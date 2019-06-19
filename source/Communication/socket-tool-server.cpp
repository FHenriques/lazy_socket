#include "socket-tool-server.h"
#include <QTcpSocket>

SocketsToolServer::SocketsToolServer(QObject *parent) : QObject(parent)
{
    this->server = nullptr;
    this->port = 23;
    _set__state(SOCKET_TOOL_SERVER__STOPPED);
}

SocketsToolServer::SocketsToolServer(quint16 port, QObject *parent) : QObject(parent)
{
    this->server = nullptr;
    this->port = port;
    _set__state(SOCKET_TOOL_SERVER__STOPPED);
}

bool SocketsToolServer::start()
{
    if(this->server){
        qDebug() << "Server is already running!";
        return false;
    }

    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()),this, SLOT(slot__new_connection()));

    qDebug() << __func__;

    if(!server->listen(QHostAddress::Any, this->port))
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
    if(server != nullptr)
        if(server->isListening())
            return this->restart();
    return false;
}

bool SocketsToolServer::stop()
{
    qDebug() << "Server stopped!";
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



void SocketsToolServer::slot__new_connection(void){
    QTcpSocket *socket = server->nextPendingConnection();
    if(this->config.welcome_message.isEnabled){
        socket->write(this->config.welcome_message.text.toLatin1());
        socket->flush();
        socket->waitForBytesWritten(this->config.welcome_message.text.length());
    }
    _set__state(SOCKET_TOOL_SERVER__LISTENING_WITH_CLIENTS);
}

void SocketsToolServer::slot__new_data_available(void){
    ;
}
void SocketsToolServer::slot__client_disconnect(void){
    ;
}



//void LazySocketServer::sig__new_connection(void)
//{

//}

//void LazySocketServer::sig__new_data_available(void){
//;
//}
void SocketsToolServer::_set__state(SocketsToolServer::SocketsToolServerState state)
{
    this->currentState = state;
    emit sig__stateChanged(state);
}
