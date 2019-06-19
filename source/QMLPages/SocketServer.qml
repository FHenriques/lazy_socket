import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import ConstVars 0.1
import SocketsToolServer 0.1
import AppVars 0.1

Item {
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
                    console.log("HERE " + state +" " + SocketServer.SOCKET_TOOL_SERVER__LISTENING_NO_CLIENTS);
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

                TextArea{
                    Layout.fillWidth: true
                    readOnly: true
                    text:"TEXT"

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
                    delegate: RowLayout{
                        anchors.left:  parent.left
                        anchors.right:  parent.right
                        height: Sizes.row_height
                        TextField{
                            id:id_textField_cmd
                            Layout.fillHeight: true
                            Layout.fillWidth:  true
                            text:"TEXT: " + index
                        }
                        Button{
                            text:qsTr("Send")
                            onClicked: {
                                id_textArea_socketData.append(id_textField_cmd.text)
                            }
                        }
                    }
                }
            }
            ColumnLayout{
                Layout.fillHeight: true
                Layout.fillWidth: true
                Text{
                    text:qsTr("Socket Data:")
                }
                TextArea{
                    id:id_textArea_socketData
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    text:""

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
