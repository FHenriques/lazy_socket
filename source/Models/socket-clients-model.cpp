#include "socket-clients-model.h"
#include "socket-clients-list.h"

ClientsModel::ClientsModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int ClientsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;
    return mList->items().size();
}

QVariant ClientsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const ClientItem item = mList->items().at(index.row());

    switch (role) {
    case IPRole:
        return QVariant(item.ip);
    case SocketHanderRole:
        return QVariant(item.socket_handler);
    case AliasRole:
        return QVariant(item.alias);
    case TimeUpRole:
        return QVariant(item.time_connected);
    case ColorRole:
        return QVariant(item.color);
    }

    return QVariant();
}

bool ClientsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    ClientItem item = mList->items().at(index.row());
    switch (role) {
    case IPRole:
        item.ip = value.toString();
        break;
    case SocketHanderRole:
        item.socket_handler = value.toInt();
        break;
    case AliasRole:
        item.alias = value.toString();
        break;
    case TimeUpRole:
        item.time_connected = value.toString();
        break;
    case ColorRole:
        item.color = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ClientsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ClientsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[IPRole] = "socket_ip";
    names[SocketHanderRole] = "socket_handler";
    names[AliasRole] = "socket_alias";
    names[TimeUpRole] = "socket_time_up";
    names[ColorRole] = "socket_color";
    return names;
}

SocketClientsList *ClientsModel::list() const
{
    return mList;
}

void ClientsModel::setList(SocketClientsList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &SocketClientsList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &SocketClientsList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &SocketClientsList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &SocketClientsList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}

bool ClientsModel::setColor(const QModelIndex &index,QString color)
{
    if (!mList)
        return false;

    ClientItem item = mList->items().at(index.row());

        item.color = color;


    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << ColorRole);
        return true;
    }
    return false;
}


