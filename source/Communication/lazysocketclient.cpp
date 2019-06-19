#include "lazysocketclient.h"

LazySocketClient::LazySocketClient(QString ip,int port,QObject *parent) :QObject(parent)
{
    this->setIp(ip);
    this->setPort(port);
}

QString LazySocketClient::getIp()
{
    return ip;
}

void LazySocketClient::setIp(QString &value)
{
    ip = value;
}

int LazySocketClient::getPort()
{
    return port;
}

void LazySocketClient::setPort(int value)
{
    port = value;
}

QString LazySocketClient::getName()
{
    if(this->name.length() == 0){
        if(socketClient->isOpen() && socketClient->state() == QTcpSocket::ConnectedState ){
          QString string = socketClient->peerName();
          name = string;
        }
    }
    return name;
}

void LazySocketClient::setName(QString &value)
{
    name = value;
}

int LazySocketClient::getUp_time()
{
    return upTime;
}

void LazySocketClient::setUp_time(int value)
{
    upTime = value;
}

QTcpSocket *LazySocketClient::getSocketClient()
{
    return socketClient;
}

void LazySocketClient::setSocketClient(QTcpSocket *value)
{
    socketClient = value;
}

int LazySocketClient::getStartTime()
{
    return startTime;
}

void LazySocketClient::setStartTime(int value)
{
    startTime = value;
}
