import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Button{
    id:customButton

    background: Rectangle{
        color:customButton.hovered ? "white" : "#F6F8F7"
    }
}
