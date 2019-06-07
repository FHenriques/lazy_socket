import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import ConstVars 0.1

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

            }

            Button{
                id:id_btn_start
                text:"Start Listening"
            }
            Rectangle{
                Layout.preferredWidth:  id_btn_start.height/2
                Layout.preferredHeight:  id_btn_start.height/2
                radius: id_btn_start.height/2
                color: "red"
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
                    text:"TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT
TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT
TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT
TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT
TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT
TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT TEXT "

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
