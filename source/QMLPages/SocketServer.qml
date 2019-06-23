import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import ConstVars 0.1
import SocketsToolServer 0.1
import UserData 0.1
import AppVars 0.1
import Qt.labs.settings 1.0
import QtQuick.Dialogs 1.0
import QMLItems 0.1

Item {
    Settings {
        category: "SocketServer"
        property alias port: id_textField_port.text
    }

    ColumnLayout{
        anchors.fill: parent
        anchors.margins: Margins.app_border
        RowLayout {
            Layout.alignment: Layout.right | Layout.bottom
            Layout.preferredHeight: Sizes.row_height
            Layout.fillHeight: false
            Text{
                Layout.fillWidth: true
                Layout.alignment:  Qt.AlignRight
                text:qsTr("Port: ")
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
            }

            TextField{
                id:id_textField_port
            }

            Button{
                id:id_btn_start
                text:AppData.socketServer_isConnected ? "Stop Listening":"Start Listening"
                onClicked: {
                    if(AppData.socketServer_isConnected){
                        socketServer.stop()
                    }else{
                        socketServer.setPort(parseInt(id_textField_port.text))
                        socketServer.start()
                    }
                }
            }
            Rectangle{
                Layout.preferredWidth:  id_btn_start.height/2
                Layout.preferredHeight:  id_btn_start.height/2
                radius: id_btn_start.height/2
                color:"black"
                function setColor(state){
                    console.log("DOING THIS")
                    switch(state){
                    case SocketsToolServer.SOCKET_TOOL_SERVER__LISTENING_WITH_CLIENTS:
                        color = "green"
                        AppData.socketServer_isConnected = true;
                        break
                    case SocketsToolServer.SOCKET_TOOL_SERVER__LISTENING_NO_CLIENTS:
                        AppData.socketServer_isConnected = true
                        color = "orange"
                        break
                    case SocketsToolServer.SOCKET_TOOL_SERVER__LISTENING_ERROR:
                        color = "red"
                        AppData.socketServer_isConnected = false
                        break
                    default:
                        color = "black"
                        AppData.socketServer_isConnected = false
                        break;
                    }
                }
                Component.onCompleted: {
                    socketServer.sig__stateChanged.connect(setColor);
                }
            }
        }

        RowLayout{
            Layout.fillHeight: true
            Layout.fillWidth: true
            ColumnLayout{
                Layout.fillHeight: true
                Layout.fillWidth: true
                Text{
                    text:qsTr("Terminal Info:")
                }

//                TextArea{
//                    Layout.fillWidth: true
//                    readOnly: true
//                    text:"TEXT"
//                }
                SocketsClientList {
                    Layout.minimumHeight:  150
                    Layout.minimumWidth: 400
                    Layout.fillWidth: true
                }
                Text{
                    text:qsTr("Commands:")
                }
                ListView{
                    Layout.minimumHeight: 8 * Sizes.row_height + 7 * Sizes.lists_delegate_gap
                    Layout.maximumHeight: 15 * Sizes.row_height + 7 * Sizes.lists_delegate_gap
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    model:30
                    spacing: Margins.lists_delegate_gap
                    clip: true
                    snapMode:ListView.SnapToItem
                    delegate: Rectangle{
                        color:"transparent"
                        anchors.left:  parent.left
                        anchors.right:  parent.right
                        height: Sizes.row_height


                        RowLayout{
                            anchors.fill:parent
                            TextField{
                                id:id_textField_cmd
                                Layout.fillHeight: true
                                Layout.fillWidth:  true
                                text:"TEXT: " + index
                            }
                            Rectangle{
                                Layout.maximumHeight:  Sizes.row_height * 0.7
                                Layout.minimumHeight:  Sizes.row_height * 0.7
                                Layout.minimumWidth: Sizes.row_height * 0.7
                                Layout.maximumWidth:  Sizes.row_height * 0.7
                                border.color: "transparent"

                                radius:height
                                color:"black"
                                MouseArea{
                                    anchors.fill: parent
                                    onClicked: {
                                        id_color_picker.visible = true
                                        console.log("choose color:")
                                    }

                                }
                            }

                            Button{
                                text:qsTr("Send")
                                onClicked: {
                                    id_textArea_socketData.append(id_textField_cmd.text)
                                }
                            }
                        }
                        RowLayout{
                            id:id_color_picker
                            visible: false
                            onVisibleChanged:visible? id_timer_close.start():null
                            Timer{
                                id:id_timer_close
                                interval: 5000
                                repeat: false
                                triggeredOnStart: false
                                onTriggered: id_color_picker.visible = false
                            }

                            anchors.left: parent.left
                            anchors.bottom: parent.bottom
                            anchors.top: parent.top
                            width: id_textField_cmd.width

                            Repeater{
                                model:5
                                Rectangle{
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    color:"blue"
                                    border.color: "red"
                                    border.width: 3
                                    MouseArea{
                                        anchors.fill: parent
                                        onClicked: {
                                            id_color_picker.visible = false
                                            console.log("Choosed Color X")
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            ColumnLayout{
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.minimumWidth:500
                Text{
                    text:qsTr("Socket Data:")
                }
                TextArea{
                    id:id_textArea_socketData
                    property int colorChanger: 0
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    textFormat: TextEdit.RichText
                    textColor: "black"
                    text:""
                    Component.onCompleted: {
                        sockets_manager.sig__new_data_arrived.connect(append_text)
                    }

                    function append_text(ip,socket_handler,message){

                        var _message = formatMessage(ip,socket_handler,message)
                        var cursorOldPosition = id_textArea_socketData.cursorPosition
                        var updateCursor = cursorOldPosition == id_textArea_socketData.text.length
                        //                        id_textArea_socketData.text += _message;
                        id_textArea_socketData.append(_message)
                        if(updateCursor)
                            id_textArea_socketData.cursorPosition = id_textArea_socketData.text.length;
                        else
                            id_textArea_socketData.cursorPosition = cursorOldPosition;

                    }
                    function formatMessage(ip,socket_handler,message){

                        var socketColor = getColor(socket_handler)
                        var colorDot ="<font size=\"4\" color=\"" + socketColor + "\">&#9679;</font>"
                        var blackDot ="<font size=\"4\" color=\"black\">&#9679;</font>"
                        var colorTXGuillemet ="<font size=\"4\" color=\"" + socketColor + "\">&#187;</font>"
                        var colorRXGuillemet ="<font size=\"4\" color=\"" + socketColor + "\">&#171;</font>"


                        var colorText = function(color,text){
                            return "<font color=\"" + color + "\">"+text+ "</font>"
                        }
                        var blackText = function(text){
                            return "<font color=\"black\">"+text+ "</font>"
                        }

                        switch(xml_user_data.qml_textFormat){
                        case UserData.TEXT__FORMAT_SIMPLE:
                            return colorDot +  " " + blackText(message)
                        case UserData.TEXT__FORMAT_IP:
                            return colorDot + blackText(ip) + colorDot +  " " + blackText(message)
                        case UserData.TEXT__FORMAT_HANDLER:
                            return colorDot + blackText(socket_handler) + colorDot +  " " + blackText(message)
                        case UserData.TEXT__FORMAT_IP_HANDLER:
                            return colorDot + blackText(ip )+ colorDot + blackText(socket_handler) + colorDot +  " " + blackText(message)
                        }
                    }

                    function getColor(socketHandler){
                        if(colorChanger++ >= 2){
                            colorChanger = 0;
                        }
                        var colorIndex = colorChanger % 3;
                        switch(colorIndex){
                        case 0:
                            return "green"
                        case 1:
                            return "red"
                        case 2:
                            return "cyan"
                        }
                    }
                }
                RowLayout{
                    Layout.preferredHeight: Sizes.row_height
                    Layout.maximumHeight:  Sizes.row_height
                    Layout.alignment: Qt.AlignRight

                    Button{
                        Layout.fillHeight: true
                        Layout.fillWidth: false
                        text:qsTr("Start Log")
                    }
                    Button{
                        Layout.fillHeight: true
                        Layout.fillWidth: false
                        text:qsTr("Clear Buffer")
                        onClicked: id_textArea_socketData.text = ""
                    }
                }
            }
        }
    }

}
