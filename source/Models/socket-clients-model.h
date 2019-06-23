#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <QAbstractListModel>

class SocketClientsList;

class ClientsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(SocketClientsList *list READ list WRITE setList)

public:
    explicit ClientsModel(QObject *parent = nullptr);

    enum {
        IPRole = Qt::UserRole,
        SocketHanderRole,
        AliasRole,
        TimeUpRole,
        ColorRole,
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    SocketClientsList *list() const;
    void setList(SocketClientsList *list);

    Q_INVOKABLE bool setColor(const QModelIndex &index,QString color);

private:
    SocketClientsList *mList;
};
Q_DECLARE_METATYPE(QModelIndex)


#endif // TODOMODEL_H
