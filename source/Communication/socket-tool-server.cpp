#include "socket-tool-server.h"
#include <QTcpSocket>
#include "clients-monitor.h"
#include <QMetaObject>

SocketsToolServer::SocketsToolServer(QObject *parent) : QTcpServer(parent)
{
    this->setPort(23);
    _set__state(SOCKET_TOOL_SERVER__STOPPED);
}

SocketsToolServer::SocketsToolServer(quint16 port, QObject *parent) : QTcpServer (parent)
{
    this->setPort(port);
    _set__state(SOCKET_TOOL_SERVER__STOPPED);
}

bool SocketsToolServer::start()
{
    if(this->isListening()){
        qDebug() << "Server is already running!";
        return false;
    }

    if(!this->listen(QHostAddress::Any, this->port))
    {
        qDebug() << "Server could not start";
        _set__state(SOCKET_TOOL_SERVER__LISTENING_ERROR);
        return false;
    }
    else
    {
        qDebug() << "Server started!";
        _set__state(SOCKET_TOOL_SERVER__LISTENING_NO_CLIENTS);
        return true;
    }

}

bool SocketsToolServer::setPort(quint16 port)
{
    if(port == this->port)
        return false;

    this->port = port;
    if(this->isListening())
        return this->restart();
    return true;
}

bool SocketsToolServer::stop()
{
    qDebug() << "Server stopped!";
    this->close();
    _set__state(SOCKET_TOOL_SERVER__STOPPED);
    return true;
}
bool SocketsToolServer::restart()
{
    this->stop();
    return this->start();
}

int SocketsToolServer::getState()
{
    return this->currentState;
}

void SocketsToolServer::config__welcome_message(QString message, bool isEnabled)
{
    this->config.welcome_message.text = message;
    this->config.welcome_message.isEnabled = isEnabled;
}

void SocketsToolServer::config__enable_welcome_message(bool isEnabled)
{
    this->config.welcome_message.isEnabled = isEnabled;
}

void SocketsToolServer::slot__new_data_available(){
    qInfo()<< "New data arrived";
    QString data;
    emit sig__new_data_available(data);
}

void SocketsToolServer::slot__client_disconnect(void){
    ;
}

void SocketsToolServer::_set__state(SocketsToolServer::SocketsToolServerState state)
{
    this->currentState = state;
    emit sig__stateChanged(state);
}




void SocketsToolServer::incomingConnection(qintptr handle)
{
    qInfo() << this << "Main thread " << QThread::currentThread();

    QThread* thread = new QThread();
    SocketsToolClient *client = new SocketsToolClient(nullptr,handle);
    client->set_client_thread(thread);


    connect(thread,&QThread::started,client,&SocketsToolClient::slot__startSocketClient);

    connect(client,&SocketsToolClient::sig__new_data_packet,SOCKET_CLIENTS_MONITOR,&SocketClientsMonitor::slot__read_from_client);

    connect(client,&SocketsToolClient::sig__started,SOCKET_CLIENTS_MONITOR,&SocketClientsMonitor::slot__add_client);

    connect(client,&SocketsToolClient::sig__started,this,&SocketsToolServer::slot__welcome_message);
    connect(client,&SocketsToolClient::sig__started,this,&SocketsToolServer::sig__new_connection);

    client->moveToThread(thread);
    thread->start();

    _set__state(SOCKET_TOOL_SERVER__LISTENING_WITH_CLIENTS);
}

void SocketsToolServer::slot__welcome_message(SocketsToolClient *client)
{
    if(this->config.welcome_message.isEnabled){
        SOCKET_CLIENTS_MONITOR->slot__write_to_client(client,this->config.welcome_message.text);
        SOCKET_CLIENTS_MONITOR->slot__write_to_client(client,QString("\n\n"));
    }
}

