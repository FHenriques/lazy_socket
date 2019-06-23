#ifndef CLIENTSMONITOR_H
#define CLIENTSMONITOR_H

#include <QObject>
#include "socket-tool-client.h"
#include "QMap"
#include <QString>

#define SOCKET_CLIENTS_MONITOR SocketClientsMonitor::getInstance()

class SocketClientsMonitor : public QObject
{
    Q_OBJECT
public:
    static SocketClientsMonitor* getInstance();
signals:
    void sig__new_data_arrived(QString ip,int socket_handler,QString message);
public slots:
    void slot__add_client(SocketsToolClient *client);
    void slot__write_to_client(SocketsToolClient *client,QString text);
    void slot__write_to_client(qintptr socketHandler,QString text);
    void slot__read_from_client(const ClientDataPacket& clientDataPacket);
    qintptr get_handler_first_socket(void);

private:
    SocketClientsMonitor()= default;
    ~SocketClientsMonitor()= default;
    SocketClientsMonitor(const SocketClientsMonitor&)= delete;
    SocketClientsMonitor& operator=(const SocketClientsMonitor&)= delete;
    QMap<qintptr,SocketsToolClient*> clients_map;

};

#endif // CLIENTSMONITOR_H
