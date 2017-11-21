import QtQuick 2.0

Rectangle {
    id: colorPicker

    signal colorPicked(color clr)

    MouseArea {
        anchors.fill: parent

        onClicked: {
            colorPicked(colorPicker.color)
        }
    }
}
