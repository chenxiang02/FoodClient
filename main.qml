import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Client.FoodConfig 1.0
import Client.Storage 1.0
import "./myComponent" as CustomComponent

Window {
    id: root
    width: 640
    height: 480
    visible: true

    Storage{
        id:message
    }

    FoodConfig{
        id:food
    }

    property int currentCategoryIndex: 0//当前索引

    property var typelist:food.foodType//类型列表
    property var foodlist: food.foodName//名字列表
    property var foodprice: food.foodPrice//价格列表
    property var typeindexlist: food.rangeBackground //索引定位
    property var itemIndex: food.itemIndex

    property var strPrice: '15'

    property var loadSuccess: food.LazyLoad//加载判断


    property var totalValue: message.totalValue //总价
    property var menuList:message.menuList//清单列表


//     头部导航栏
    Rectangle {
        id: header
        width: parent.width
        height: 50
        color: "lightblue"
        anchors.top: parent.top
        visible: loadSuccess//懒加载

        Text {
            text: "店铺名称"
            anchors.centerIn: parent
            visible: loadSuccess //懒加载

        }
    }

    Rectangle{
        id:typeMenuList
        anchors.top: header.bottom
        anchors.left: parent.left
        width: parent.width / 4
        height: parent.height - header.height - bottomBar.height
        color: "#F6F8F7"
        visible: loadSuccess //懒加载
        Column{
            Repeater{
                model: typelist
                visible: loadSuccess//懒加载

                delegate: CustomComponent.CustomButton{
                    id:btn
                    width: typeMenuList.width
                    height: 50
                    text: qsTr(typelist[index])
                    Layout.alignment: Qt.AlignHCenter

                    backgoundColor.color: (listview.contentY>=typeindexlist[index] && listview.contentY < typeindexlist[index+1])
                                           ? "white" : "#F6F8F7"

                    onClicked: {
                        listview.positionViewAtIndex(itemIndex[index],listview.Center)
                    }
                }
            }
        }
    }

    Rectangle{
        width: parent.width - typeMenuList.width
        height: parent.height - header.height - bottomBar.height
        anchors.top: header.bottom
        anchors.right: parent.right
        visible: loadSuccess
        clip: true
        ListView{
            id:listview
            anchors.fill: parent
            model: foodlist
            spacing:10

            delegate:CustomComponent.CustomItem {
                width: listview.width
                height: 50
                customMonicker.text: qsTr(foodlist[index])
                customValue.text: qsTr(loadSuccess ? foodprice[index]:strPrice)

                countFlag: message.clearCountFlag //是否清除count 资源消耗过大 可以考虑优化

                addBtn.onClicked:{
                    countText.text = parseInt(countText.text) + 1
                    let mList = [customMonicker.text,countText.text,customValue.text]
                    message.addTotalValue(mList)
                }


                subtracttBtn.onClicked:{
                    if(countText.text>0)
                    {
                         countText.text = countText.text - 1
                         let mList = [customMonicker.text,countText.text,customValue.text]
                         message.subtractValue(mList)
                    }
            }
        }
       }
    }


    Rectangle{
        id:bottomBar
        visible: loadSuccess
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width / 2 * 1.5
        height: 60
        color: "black"
        radius: 25
        opacity: 0.8

        Label{
            text: qsTr("$ "+totalValue)
            color: "white"
            font.pixelSize: 24
            font.bold: true
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
        Button
        {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 20
            text: qsTr("确认")

            background: Rectangle{
                color: "pink"
                radius: 12
            }

            onClicked: {
                menuBar.visible = true;
            }
        }
    }

    BusyIndicator{
        visible: !loadSuccess
        anchors.fill: parent
        running: !loadSuccess
    }

    Text {
        text: qsTr("当前服务器正忙")
        anchors.centerIn: parent
        visible: !loadSuccess
    }

    CustomComponent.CustomMenuBar{
        id:menuBar
        width: parent.width / 2
        height: parent.height / 2
        anchors.centerIn: parent
        visible: false
        menuStr:menuList

        sendClick.onClicked: {
            food.sendMenuList(menuList,totalValue)
            message.clearMenuList()
            message.totalValue = 0
            menuBar.visible = false
            message.clearCountFlag = true
        }
    }
}
