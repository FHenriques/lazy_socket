#include "clients-monitor.h"

SocketClientsMonitor* SocketClientsMonitor::getInstance(){
    static SocketClientsMonitor* pSingleInstance = nullptr;
    if ( pSingleInstance == nullptr ){
        pSingleInstance= new SocketClientsMonitor();
    }
    return pSingleInstance;
}

void SocketClientsMonitor::slot__add_client(SocketsToolClient *client)
{
    clients_map.insert(client->getSocketHandler(),client);
}

void SocketClientsMonitor::slot__write_to_client(SocketsToolClient *client, QString text)
{
    QMetaObject::invokeMethod(client, "slot__write", Qt::QueuedConnection,Q_ARG(QString, text));
}

void SocketClientsMonitor::slot__write_to_client(qintptr socketHandler, QString text)
{
    SocketsToolClient *client = clients_map.value(socketHandler);
    this->slot__write_to_client(client, text);
}

void SocketClientsMonitor::slot__read_from_client(const ClientDataPacket &clientDataPacket)
{
    emit sig__new_data_arrived(
                clientDataPacket.getPeer_ip().split(":").last(),
                clientDataPacket.getHandler_socket(),
                clientDataPacket.getData_payload()
                );
}

qintptr SocketClientsMonitor::get_handler_first_socket()
{
    return clients_map.first()->getSocketHandler();
}
