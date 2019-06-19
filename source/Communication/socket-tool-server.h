#ifndef LAZYSOCKETSERVER_H
#define LAZYSOCKETSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QQmlEngine>


class SocketsToolServer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SocketsToolServerState currentState READ getCurrentState)

public:


    enum SocketsToolServerState
    {
        SOCKET_TOOL_SERVER__STOPPED,
        SOCKET_TOOL_SERVER__PAUSED,
        SOCKET_TOOL_SERVER__LISTENING_WITH_CLIENTS,
        SOCKET_TOOL_SERVER__LISTENING_NO_CLIENTS,
        SOCKET_TOOL_SERVER__LISTENING_MAX_CLIENTS,
        SOCKET_TOOL_SERVER__LISTENING_ERROR,
    };
    Q_ENUMS(SocketsToolServerState)


    explicit SocketsToolServer(QObject *parent = nullptr);
    explicit SocketsToolServer(quint16 port,QObject *parent = nullptr);
    Q_INVOKABLE bool start(void);
    Q_INVOKABLE bool setPort(quint16 port);
    Q_INVOKABLE bool stop(void);
    Q_INVOKABLE bool restart(void);
    Q_INVOKABLE int getState(void);
//    Q_INVOKABLE bool disconnectClientByIP(QString ip);
//    Q_INVOKABLE bool disconnectClientByHandler(QTcpSocket* socket_handler);
//    Q_INVOKABLE bool setListenPort(void);

    SocketsToolServerState getCurrentState()
    { return currentState; }

    void config__welcome_message(QString message,bool isEnabled);
    void config__enable_welcome_message(bool isEnabled);
signals:
    void sig__new_connection(void);
    void sig__new_data_available(void);
    void sig__serverStarted(void);
    void sig__stateChanged(SocketsToolServerState state);
    void sig__error(void);

public slots:
    void slot__new_connection(void);
    void slot__new_data_available(void);
    void slot__client_disconnect(void);

private:
    void _set__state(SocketsToolServerState state);
    quint16 port;
    SocketsToolServerState currentState;
    QTcpServer *server;
    struct{
        struct{
            QString text = "";
            bool isEnabled = 0;
        }welcome_message;
    }config;
};

#endif // LAZYSOCKETSERVER_H
