import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("07ColorPicker")

    Text {
        id: helloText
        text: qsTr("Hello World!")
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        font.pointSize: 30
    }

    ColorPicker {
        id: redPicker
        color: "red"

        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30

        KeyNavigation.right: bluePicker
        KeyNavigation.tab: bluePicker

        onColorPicked: {
            helloText.color = clr
        }
    }

    ColorPicker {
        id: bluePicker
        color: "blue"

        anchors.left: redPicker.right
        anchors.leftMargin: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30

        KeyNavigation.left: redPicker
        KeyNavigation.right: greenPicker
        KeyNavigation.tab: greenPicker
    }

    ColorPicker {
        id: greenPicker
        color: "green"

        anchors.left: bluePicker.right
        anchors.leftMargin: 30
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30

        KeyNavigation.left: bluePicker
        KeyNavigation.tab: redPicker
    }

    function setHelloTextColor(clr) {
        helloText.color = clr
    }

    Component.onCompleted: {
        bluePicker.colorPicked.connect(setHelloTextColor)
        greenPicker.colorPicked.connect(setHelloTextColor)
    }
}

















