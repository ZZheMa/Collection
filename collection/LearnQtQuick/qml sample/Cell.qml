import QtQuick 2.0

Rectangle {
    id: cell

    property color cellColor: "transparent"

    width: 48
    height: 32
    color: cellColor

    signal mouseLeftClicked

    MouseArea {
        id: cellMouseArea
        anchors.fill: parent

        onClicked: mouseLeftClicked()
    }
}
