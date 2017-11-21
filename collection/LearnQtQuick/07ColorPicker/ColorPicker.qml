import QtQuick 2.0

Rectangle {
    id: colorPicker

    implicitWidth: 50
    implicitHeight: 50
    radius: 10
    antialiasing: true

    signal colorPicked(color clr)

    MouseArea {
        anchors.fill: parent

        onClicked: {
            colorPicked(colorPicker.color)
            mouse.accepted = true
            colorPicker.focus = true
        }

        hoverEnabled: true
        onEntered: {
            colorPicker.border.color = "gray"
            colorPicker.border.width = 3
        }

        onExited: {
            colorPicker.border.color = "lightgray"
            colorPicker.border.width = 1
        }
    }

    Keys.onSpacePressed: {
        colorPicked(colorPicker.color)
        event.accepted = true
    }

    Keys.onReturnPressed: {
        colorPicked(colorPicker.color)
        event.accepted = true
    }

    function configureBorder() {
        colorPicker.border.width = colorPicker.focus ? 3 : 1
        colorPicker.border.color = colorPicker.focus ? "gray" : "lightgray"
    }

    onFocusChanged: {
        configureBorder()
    }

    Component.onCompleted: {
        configureBorder()
    }
}









