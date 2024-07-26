import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Client.Storage 1.0
import "../myComponent" as CustomPonent

Item{
    id:menuBar

    Storage{
        id:menu
    }

    Rectangle{
        anchors.fill: parent
        color: "white"
    }

    property alias menuStr: menu.menuList
    property alias sendClick: affirm

    property var str0: "value"

    Rectangle{
        id:header
        anchors.top: parent.top
        width: parent.width
        height: parent.height / 8
        color: "lightblue"

        Label{
            text: qsTr("菜单")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    ScrollView{
        id:scrollList
        anchors.top: header.bottom
        width: parent.width
        height: parent.height - bottom.height - header.height

        clip: true
        Column{
            spacing: 5
            Repeater{
                model: menuStr.length === 0 ? 0 : menuStr.length / 3

                delegate: CustomPonent.MenuItem{
                    width: scrollList.width
                    leftText.text:qsTr(menuStr.length === 0 ? str0 : menuStr[index * 3])
                    centerText.text: qsTr(menuStr.length === 0 ? str0 : menuStr[index * 3 + 1])
                    rightText.text: qsTr(menuStr.length === 0 ? str0 : menuStr[index * 3 + 2])
                }
            }
        }
    }

    Rectangle{
        id:bottom
        anchors.top: scrollList.bottom
        width: parent.width
        height: parent.height / 8 + 10

        color: "gray"

        Button{
            id:affirm
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("确认")
            width: 100

            background: Rectangle{
                radius: 10
                color: affirm.hovered ? "#2DAAE1" : "white"
                border.color: affirm.hovered ? "lightgreen" : "white"
            }
        }
        Button{
            id:cancel
            anchors.right: parent.right
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("取消")
            width: 100

            background: Rectangle{
                radius: 10
                color: cancel.hovered ? "#2DAAE1" : "white"
                border.color: cancel.hovered ? "lightgreen" : "white"
            }

            onClicked: {
                menuBar.visible = false
            }
        }
    }
}
