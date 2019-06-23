#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QVector>
#include "Communication/clients-monitor.h"

struct ClientItem
{
    QString ip;
    int socket_handler;
    QString alias;
    QString time_connected;
    QString color;
};

class SocketClientsList : public QObject
{
    Q_OBJECT
public:
    explicit SocketClientsList(QObject *parent = nullptr);

    QVector<ClientItem> items() const;

    bool setItemAt(int index, const ClientItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem(SocketsToolClient * client);
    void removeItem(int index);
    void removeAll(void);
private:
    QVector<ClientItem> mItems;
};

#endif // TODOLIST_H
