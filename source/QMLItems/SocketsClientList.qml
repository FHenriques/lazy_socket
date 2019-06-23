import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import SocketClientsModel 1.0
import QtQml.Models 2.3

Rectangle {
    id:root
    property int removeIndex: 0
    property int changeColorIndex:0

    ColorDialog {
        id: id_dialog_colorPicker
        title: "Please choose a color"
        onAccepted: {
            socketClientsModel.setColor(id_listView_sockeClientsList.model.modelIndex(changeColorIndex),id_dialog_colorPicker.color.toString())
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    MessageDialog {
        id: id_dialog_close_socket
        visible: false
        title:qsTr("Warning!")
        informativeText: qsTr("Remove socket?\n")
        standardButtons: StandardButton.Yes | StandardButton.No
    }
    Connections {
        target: id_dialog_close_socket
        onYes: {
            id_dialog_close_socket.close()
            socketClientsList.removeItem(removeIndex)
        }
    }
    MessageDialog {
        id: id_dialog_close_all
        visible: false
        title:qsTr("Warning!")
        informativeText: qsTr("Remove all socket connections?\n")
        standardButtons: StandardButton.Yes | StandardButton.No
    }
    Connections {
        target: id_dialog_close_all
        onYes: {
            id_dialog_close_all.close()
            socketClientsList.removeAll()
        }
    }

    ScrollView{
        anchors.fill: parent
        contentItem:ListView {
            id:id_listView_sockeClientsList
            anchors.fill: parent
            clip: true
            snapMode: ListView.SnapToItem
            interactive: true

            model:id_delegateModel_socketClients
            headerPositioning: ListView.OverlayHeader
            header : Rectangle{
                id:id_header_clientsList
                anchors.left: parent.left
                anchors.right: parent.right
                height: 30
                color:"#EEEEEE"
                border.color:"#DDDDDD"
                property int text_padding: 6
                property int separator_vertical_margin: 8

                RowLayout {
                    anchors.fill:parent
                    anchors.rightMargin: id_header_clientsList.text_padding
                    Rectangle{
                        color:"transparent"
                        Layout.fillHeight: true
                        Layout.minimumWidth: 90
                        Text{
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment:  Text.AlignVCenter
                            text:qsTr("IP")
                        }
                        Rectangle{
                            width: 1
                            color:"black"
                            anchors.horizontalCenter: parent.right
                            anchors.top: parent.top
                            anchors.topMargin: id_header_clientsList.separator_vertical_margin
                            anchors.bottomMargin:  id_header_clientsList.separator_vertical_margin
                            anchors.bottom:  parent.bottom
                        }
                    }
                    Rectangle{
                        color:"transparent"
                        Layout.fillHeight: true
                        Layout.fillWidth:  true
                        Layout.maximumWidth: 40
                        Layout.minimumWidth: 40
                        Text{
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment:  Text.AlignVCenter
                            text:qsTr("handler")
                        }
                        Rectangle{
                            width: 1
                            color:"black"
                            anchors.horizontalCenter: parent.right
                            anchors.top: parent.top
                            anchors.topMargin: id_header_clientsList.separator_vertical_margin
                            anchors.bottomMargin:  id_header_clientsList.separator_vertical_margin
                            anchors.bottom:  parent.bottom
                        }
                    }
                    Rectangle{
                        color:"transparent"
                        Layout.fillHeight: true
                        Layout.fillWidth:  true
                        Text{
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment:  Text.AlignVCenter
                            text:qsTr("alias")
                        }
                        Rectangle{
                            width: 1
                            color:"black"
                            anchors.horizontalCenter: parent.right
                            anchors.top: parent.top
                            anchors.topMargin: id_header_clientsList.separator_vertical_margin
                            anchors.bottomMargin:  id_header_clientsList.separator_vertical_margin
                            anchors.bottom:  parent.bottom
                        }
                    }
                    Rectangle{
                        color:"transparent"
                        Layout.fillHeight: true
                        Layout.fillWidth:  true
                        Layout.minimumWidth: 50
                        Layout.maximumWidth: 95
                        Text{
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment:  Text.AlignVCenter
                            text:qsTr("con. time")
                        }
                        Rectangle{
                            width: 1
                            color:"black"
                            anchors.horizontalCenter: parent.right
                            anchors.top: parent.top
                            anchors.topMargin: id_header_clientsList.separator_vertical_margin
                            anchors.bottomMargin:  id_header_clientsList.separator_vertical_margin
                            anchors.bottom:  parent.bottom
                        }
                    }

                    Button{
                        Layout.fillHeight: true
                        Layout.topMargin: 5
                        Layout.bottomMargin:  5
                        Layout.maximumWidth: height * 6.25
                        Layout.preferredWidth: height * 6.25
                        Layout.minimumWidth: height * 6.25
                        text:qsTr("Disconnect All")
                        onClicked: {
                            id_dialog_close_all.open()
                        }
                    }
                }
            }
        }
    }

    DelegateModel {
        id: id_delegateModel_socketClients
        model: SocketClientsModel {
            id:socketClientsModel
            list: socketClientsList
        }

        delegate: Rectangle{
            id:id_layout_clientsList
            anchors.left: parent.left
            anchors.right: parent.right
            height: 30
            color:index % 2?"#EEEEEE":"#DDDDDD"
            property int text_padding: 6
            property int separator_vertical_margin: 8
            RowLayout {
                anchors.fill:parent
                anchors.rightMargin: id_layout_clientsList.text_padding
                Rectangle{
                    color:"transparent"
                    Layout.fillHeight: true
                    Layout.minimumWidth: 90
                    Text{
                        padding: id_layout_clientsList.text_padding
                        id:id_text_ip
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment:  Text.AlignVCenter
                        text:socket_ip
                    }
                    Rectangle{
                        width: 1
                        color:"black"
                        anchors.horizontalCenter: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: id_layout_clientsList.separator_vertical_margin
                        anchors.bottomMargin:  id_layout_clientsList.separator_vertical_margin
                        anchors.bottom:  parent.bottom
                    }
                }
                Rectangle{
                    color:"transparent"
                    Layout.fillHeight: true
                    Layout.fillWidth:  true
                    Layout.maximumWidth: 40
                    Layout.minimumWidth: 40
                    Text{
                        anchors.fill: parent
                        text:""+socket_handler
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment:  Text.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        color:"black"
                        anchors.horizontalCenter: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: id_layout_clientsList.separator_vertical_margin
                        anchors.bottomMargin:  id_layout_clientsList.separator_vertical_margin
                        anchors.bottom:  parent.bottom
                    }
                }
                Rectangle{
                    color:"transparent"
                    Layout.fillHeight: true
                    Layout.fillWidth:  true
                    Text{
                        anchors.fill: parent
                        text:socket_alias
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment:  Text.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        color:"black"
                        anchors.horizontalCenter: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: id_layout_clientsList.separator_vertical_margin
                        anchors.bottomMargin:  id_layout_clientsList.separator_vertical_margin
                        anchors.bottom:  parent.bottom
                    }
                }
                Rectangle{
                    color:"transparent"
                    Layout.fillHeight: true
                    Layout.fillWidth:  true
                    Layout.minimumWidth: 50
                    Layout.maximumWidth: 95
                    Text{
                        anchors.fill: parent
                        text:socket_time_up
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment:  Text.AlignVCenter
                    }
                    Rectangle{
                        width: 1
                        color:"black"
                        anchors.horizontalCenter: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: id_layout_clientsList.separator_vertical_margin
                        anchors.bottomMargin: id_layout_clientsList.separator_vertical_margin
                        anchors.bottom:  parent.bottom
                    }
                }
                Rectangle{
                    Layout.fillHeight: true
                    Layout.maximumWidth: 2*height
                    Layout.preferredWidth: 2* height
                    Layout.minimumWidth:   2*height
                    color:"transparent"
                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            changeColorIndex = index
                            id_dialog_colorPicker.open()
                        }
                    }
                    Rectangle{
                        anchors.bottom: parent.verticalCenter
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.margins: 3
                        radius: height
                        color:socket_color

                    }

                    Text{
                        anchors.top: parent.verticalCenter
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        text:socket_color
                        font.pixelSize: 10
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment:  Text.AlignTop
                    }
                }
                Button{
                    Layout.fillHeight: true
                    Layout.topMargin: 5
                    Layout.bottomMargin:  5
                    Layout.maximumWidth: height * 3
                    Layout.preferredWidth: height * 3
                    Layout.minimumWidth: height * 3
                    text:"Disconnect"
                    onClicked: {
                        removeIndex = index
                        id_dialog_close_socket.open()
                    }
                }
            }
        }

    }
}
