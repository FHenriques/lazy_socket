#ifndef LAZYSOCKETSERVER_H
#define LAZYSOCKETSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QQmlEngine>
#include <QThreadPool>
#include "socket-tool-client.h"

class SocketsToolServer : public QTcpServer
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
    void sig__new_connection(SocketsToolClient *client);
    void sig__new_data_available(QString data);
    void sig__serverStarted(void);
    void sig__stateChanged(SocketsToolServerState state);
    void sig__error(void);
    void sig__write(QString data);

public slots:
    void slot__new_data_available(void);
    void slot__client_disconnect(void);
    void slot__welcome_message(SocketsToolClient *client);
private:
    void _set__state(SocketsToolServerState state);
    quint16 port;
    SocketsToolServerState currentState;
    struct{
        struct{
            QString text = "";
            bool isEnabled = 0;
        }welcome_message;
    }config;

    QThreadPool pool;

protected:
    virtual void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;
};

#endif // LAZYSOCKETSERVER_H
