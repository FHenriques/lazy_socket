#ifndef LAZYSOCKETCLIENT_H
#define LAZYSOCKETCLIENT_H

#include <QObject>
#include <QTcpSocket>

class LazySocketClient : public QObject
{
    Q_OBJECT
public:
    explicit LazySocketClient(QString ip = "127.0.0.1", int port = 23,QObject *parent = nullptr);

    QString getIp() ;
    void setIp(QString &value);

    int getPort() ;
    void setPort(int value);

    QString getName() ;
    void setName(QString &value);

    int getUp_time() ;
    void setUp_time(int value);

    QTcpSocket *getSocketClient() ;
    void setSocketClient(QTcpSocket *value);

    int getStartTime() ;
    void setStartTime(int value);

signals:

public slots:


private:
    QString ip = "127.0.0.1";
    int port = 23;
    QString name;
    int startTime = -1;
    int upTime = - 1;
    QTcpSocket *socketClient;
};

#endif // LAZYSOCKETCLIENT_H
