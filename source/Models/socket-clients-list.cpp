#include "socket-clients-list.h"
#include <QDebug>
#include <QDateTime>

SocketClientsList::SocketClientsList(QObject *parent) : QObject(parent)
{
    //    mItems.append({ "192.168.1.2", 2000, "Socket 1","10:26","#0000FF"});
    //    mItems.append({ "192.168.1.3", 2001, "Socket 2","10:30","#00FFFF"});
    //    mItems.append({ "192.168.2.100", 2011, "Socket 3","11:30","#FF0000"});
    //    mItems.append({ "192.168.1.2", 2000, "Socket 1","10:26","#0000FF"});
    //    mItems.append({ "192.168.1.3", 2001, "Socket 2","10:30","#00FFFF"});
    //    mItems.append({ "192.168.2.100", 2011, "Socket 3","11:30","#FF0000"});
    //    mItems.append({ "192.168.1.2", 2000, "Socket 1","10:26","#0000FF"});
    //    mItems.append({ "192.168.1.3", 2001, "Socket 2","10:30","#00FFFF"});
    //    mItems.append({ "192.168.2.100", 2011, "Socket 3","11:30","#FF0000"});
    //    mItems.append({ "192.168.1.2", 2000, "Socket 1","10:26","#0000FF"});
    //    mItems.append({ "192.168.1.3", 2001, "Socket 2","10:30","#00FFFF"});
    //    mItems.append({ "192.168.2.100", 2011, "Socket 3","11:30","#FF0000"});
    //    mItems.append({ "192.168.1.2", 2000, "Socket 1","10:26","#0000FF"});
    //    mItems.append({ "192.168.1.3", 2001, "Socket 2","10:30","#00FFFF"});
    //    mItems.append({ "192.168.2.100", 2011, "Socket 3","11:30","#FF0000"});
    //    mItems.append({ "192.168.1.2", 2000, "Socket 1","10:26","#0000FF"});
    //    mItems.append({ "192.168.1.3", 2001, "Socket 2","10:30","#00FFFF"});
    //    mItems.append({ "192.168.2.100", 2011, "Socket 3","11:30","#FF0000"});
    //    mItems.append({ "192.168.1.2", 2000, "Socket 1","10:26","#0000FF"});
    //    mItems.append({ "192.168.1.3", 2001, "Socket 2","10:30","#00FFFF"});
    //    mItems.append({ "192.168.2.100", 2011, "Socket 3","11:30","#FF0000"});
    //    mItems.append({ "192.168.1.2", 2000, "Socket 1","10:26","#0000FF"});
    //    mItems.append({ "192.168.1.3", 2001, "Socket 2","10:30","#00FFFF"});
    //    mItems.append({ "192.168.2.100", 2011, "Socket 3","11:30","#FF0000"});
    //    mItems.append({ "192.168.1.2", 2000, "Socket 1","10:26","#0000FF"});
    //    mItems.append({ "192.168.1.3", 2001, "Socket 2","10:30","#00FFFF"});
    //    mItems.append({ "192.168.2.100", 2011, "Socket 3","11:30","#FF0000"});
    //    mItems.append({ "192.168.1.2", 2000, "Socket 1","10:26","#0000FF"});
    //    mItems.append({ "192.168.1.3", 2001, "Socket 2","10:30","#00FFFF"});
    //    mItems.append({ "192.168.2.100", 2011, "Socket 3","11:30","#FF0000"});
}

QVector<ClientItem> SocketClientsList::items() const
{
    return mItems;
}

bool SocketClientsList::setItemAt(int index, const ClientItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const ClientItem &oldItem = mItems.at(index);
    if (
            item.ip == oldItem.ip
            && item.socket_handler == oldItem.socket_handler
            && item.alias == oldItem.alias
            && item.time_connected == oldItem.time_connected
            && item.color == oldItem.color
            )
        return false;

    mItems[index] = item;
    return true;
}

void SocketClientsList::appendItem(SocketsToolClient * client)
{
    ClientItem item;
    QDateTime time = QDateTime::currentDateTime();
    QString formatedDate;
    QStringList months = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
    if(false){
        formatedDate = QString().sprintf("%03s/%02d - %02:%02d:%02d",
                                         static_cast<const char*>(months.at(time.date().month()-1).toLatin1()),
                                         time.date().day(),
                                         time.time().hour(),
                                         time.time().minute(),
                                         time.time().second()
                                         );
    }else{

        formatedDate = QString().sprintf("%02d/%03s - %02d:%02d:%02d",
                                         time.date().day(),
                                         static_cast<const char*>(months.at(time.date().month()-1).toLatin1()),
                                         time.time().hour(),
                                         time.time().minute(),
                                         time.time().second()
                                         );
    }
    item.ip = client->get_client_ip();
    item.alias = "";
    item.socket_handler = client->getSocketHandler();
    item.time_connected = formatedDate;
    item.color = "black";
    emit preItemAppended();
    mItems.append(item);
    emit postItemAppended();
}

void SocketClientsList::removeItem(int index)
{
    emit preItemRemoved(index);
    mItems.removeAt(index);
    emit postItemRemoved();
}

void SocketClientsList::removeAll(void)
{
    while( mItems.count()) {
        removeItem(0);
    }
}
