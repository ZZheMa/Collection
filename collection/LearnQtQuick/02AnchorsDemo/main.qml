import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Anchors Demo")

    Rectangle {
        id: leftRect
        width: 200
        height: 200

        color: "blue"

        border.width: 5
        border.color: "red"

        antialiasing: true
        radius: 10

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 50
    }

    Rectangle {
        id: rightRect
        width: 200
        height: 200

        color: "red"

        border.width: 5
        border.color: "blue"

        antialiasing: true
        radius: 10

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 50
    }
}
