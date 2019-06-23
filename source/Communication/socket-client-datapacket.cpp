#include "socket-client-datapacket.h"

ClientDataPacket::ClientDataPacket(void)
{
    this->handler_socket = 0;
    this->peer_ip = "";
    this->data_payload = "";
}

ClientDataPacket::ClientDataPacket(const ClientDataPacket & clientDataPacket)
{
    this->data_payload = clientDataPacket.data_payload;
    this->handler_socket= clientDataPacket.handler_socket;
    this->peer_ip= clientDataPacket.peer_ip;
    this->peer_name= clientDataPacket.peer_name;
    this->runningThread = nullptr;
}

qintptr ClientDataPacket::getHandler_socket() const
{
    return handler_socket;
}

void ClientDataPacket::setHandler_socket(const qintptr &value)
{
    handler_socket = value;
}

QString ClientDataPacket::getPeer_ip() const
{
    return peer_ip;
}

void ClientDataPacket::setPeer_ip(const QString &value)
{
    peer_ip = value;
}

QString ClientDataPacket::getData_payload() const
{
    return data_payload;
}

void ClientDataPacket::setData_payload(const QString &value)
{
    data_payload = value;
}

QString ClientDataPacket::getPeer_name() const
{
    return peer_name;
}

void ClientDataPacket::setPeer_name(const QString &value)
{
    peer_name = value;
}

QThread *ClientDataPacket::getRunningThread() const
{
    return runningThread;
}

void ClientDataPacket::setRunningThread(QThread *value)
{
    runningThread = value;
}
