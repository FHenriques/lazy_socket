#include "socket-tool-client.h"
#include <QString>
#include <QHostAddress>

SocketsToolClient::SocketsToolClient(QObject *parent, qintptr socketHandler) : QObject(parent)
{
    this->socketHandler = socketHandler;
    this->socketClient = nullptr;

}

void SocketsToolClient::slot__startSocketClient(void){
    this->socketClient = new QTcpSocket(nullptr);
    if(!this->socketClient->setSocketDescriptor(this->socketHandler))
    {
        qCritical() << this->socketClient->errorString();
        delete this->socketClient;
        return;
    }
    connect(this->socketClient, &QTcpSocket::readyRead, this,&SocketsToolClient::slot__new_data_available);
    emit sig__started(this);
}





void SocketsToolClient::slot__new_data_available()
{
    ClientDataPacket dataPacket;
    QByteArray rawData = this->socketClient->readAll();
    QString  message = priv_chop_terminators(QString::fromLatin1(rawData.data()));
    if(message.length() == 0)
        return;
    dataPacket.setData_payload(message);
    dataPacket.setPeer_ip(this->get_client_ip());
    dataPacket.setPeer_name(this->socketClient->peerName());
    dataPacket.setHandler_socket(this->socketHandler);
    dataPacket.setRunningThread(QThread::currentThread());
    emit sig__new_data_packet(dataPacket);
}



QString SocketsToolClient::get_client_ip()
{
    return this->socketClient->peerAddress().toString().split(":").last();
}

void SocketsToolClient::set_client_thread(QThread *socketClientThread)
{
    this->socketClientThread = socketClientThread;
}

QThread *SocketsToolClient::get_client_thread()
{
    return this->socketClientThread;
}

void SocketsToolClient::slot__write(QString data)
{
    this->socketClient->write(data.toLatin1());
}

qintptr SocketsToolClient::getSocketHandler() const
{
    return socketHandler;
}




/**

 PRIVATE FUNCTIONS

 */


QString SocketsToolClient::priv_chop_terminators(QString message){

    //The richbox text add terminators for each append, any terminators here will be chopped
    while(true){
        if(message.length() == 0)
            return "";
        if(message.at(message.length()-1) == '\n' ||message.at(message.length()-1) == '\r'){
            message.chop(1);
        }else{
            break;
        }
    }

    //The final text box will be in rich text, this way it will bypass the rich text parser and show correctly the '<' and '>' chars.
    message.replace('<',"&lt;");
    message.replace('>',"&gt;");

    //This probably be better be processed by the richboxtext, but here it will be processed in c++ instead of javascript.
    return message;
}
