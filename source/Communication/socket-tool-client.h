#ifndef SOCKET_TOOL_CLIENT_H
#define SOCKET_TOOL_CLIENT_H

#include <QObject>
#include <QDebug>
#include <QRunnable>
#include <QThread>
#include <QTcpSocket>
#include "socket-client-datapacket.h"
class SocketsToolClient : public QObject
{
    Q_OBJECT
public:
    explicit SocketsToolClient(QObject *parent = nullptr, qintptr handle = 0);

    QString     get_client_ip(void);
    void        set_client_thread(QThread * socketClientThread);
    QThread*    get_client_thread(void);


    qintptr getSocketHandler() const;

signals:
    void sig__new_data_packet(const ClientDataPacket& clientDataPacket);
    void sig__started(SocketsToolClient* ptr);

public slots:
    void slot__new_data_available(void);
    void slot__startSocketClient(void);
    void slot__write(QString data);

private:
    QString priv_chop_terminators(QString message);

    qintptr socketHandler;
    QTcpSocket* socketClient;
    QThread * socketClientThread;
    QString color;
    QString connectionTime;
    QString alias;
};

#endif // CLIENT_H
