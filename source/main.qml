import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 1.4
import QMLPages 0.1

Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("LazySocket v0.1")

    TabView{
        anchors.fill: parent
        Tab {
            title: "Socket Client"

        }
        Tab {
            title: "SocketServer"
            SocketServer{
                anchors.fill: parent
            }
        }
        Tab {
            title: "Serial"
            Rectangle {

            }
        }
    }

}
