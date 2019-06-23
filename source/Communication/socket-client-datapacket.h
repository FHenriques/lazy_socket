#ifndef CLIENTDATAPACKET_H
#define CLIENTDATAPACKET_H

#include <QObject>

class ClientDataPacket
{
public:
    explicit ClientDataPacket(void);
    explicit ClientDataPacket(const ClientDataPacket&);

    qintptr getHandler_socket() const;
    void setHandler_socket(const qintptr &value);

    QString getPeer_ip() const;
    void setPeer_ip(const QString &value);

    QString getData_payload() const;
    void setData_payload(const QString &value);

    QString getPeer_name() const;
    void setPeer_name(const QString &value);

    QThread* getRunningThread() const;
    void setRunningThread(QThread* value);

signals:

public slots:
private:
    qintptr handler_socket;
    QThread *runningThread;
    QString peer_ip;
    QString peer_name;
    QString data_payload;
};
Q_DECLARE_METATYPE(ClientDataPacket);
#endif // CLIENTDATAPACKET_H
