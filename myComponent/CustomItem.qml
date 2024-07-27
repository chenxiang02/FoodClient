import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Client.Storage 1.0

Item{
    id:customItem

    Storage{
        id:clearcount

    }

    property alias customMonicker:customName //菜名文本
    property alias customValue: customPrice //价格文本
    property alias countText: count

    property alias addBtn: add //添加按钮
    property alias subtracttBtn: subtract //减少按钮

    property var countFlag: clearcount.clearCountFlag

    onCountFlagChanged: {
        if(countFlag)
        {
            count.text = "0"
            clearcount.clearCountFlag = false
        }
    }

    Rectangle{
        id:backColor
        anchors.fill: parent

        MouseArea{
            id:mouseBack
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                backColor.color = "#FFFD99"
            }
            onExited: {
                backColor.color = "white"
            }
        }

    }

    Text {
       id:customName
       text: qsTr("text")
       anchors.right: customPrice.left
       anchors.rightMargin: 20
       anchors.verticalCenter: parent.verticalCenter
    }
    Text {
       id:customPrice
       text: qsTr("text")
       anchors.right:add.left
       anchors.rightMargin: parent.width / 4
       anchors.verticalCenter: parent.verticalCenter
    }
    Button{
      id:add
      text:qsTr("+")
      width: 28
      height: 28
      anchors.verticalCenter: parent.verticalCenter
      anchors.right: count.left
      anchors.rightMargin: 8

      background: Rectangle{
          color: "#FEDA07"
          radius: 14
      }
    }

    Text {
      id: count
      font.pixelSize: 18
      text: qsTr("0")
      anchors.verticalCenter: parent.verticalCenter
      anchors.right: subtract.left
      anchors.rightMargin: 8
    }

    Button{
      id:subtract
      width: 28
      height: 28
      text: qsTr("-")
      anchors.verticalCenter: parent.verticalCenter
      anchors.right: parent.right
      anchors.rightMargin: 20

      background: Rectangle{
          color: "#FEDA07"
          radius: 14
      }
    }
}
