import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Client.Storage 1.0


Item{
    width:200
    height: 50
    Rectangle{
        anchors.fill: parent
        color: "pink"
    }

    property alias leftText: text1
    property alias centerText: text2
    property alias rightText: text3

    Label{
        id:text1
        text: qsTr("text")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 20
        color: "white"
    }

    Label{
        id:text2
        text: qsTr("text")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: "white"
    }

    Label{
        id:text3
        text: qsTr("text")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 20
        color: "white"
    }
}
