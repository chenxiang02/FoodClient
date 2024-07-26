import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Button{
    id:customButton

    property alias backgoundColor: background.color

    background: Rectangle{
        id:background
    }
}
