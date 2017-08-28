import QtQuick 2.0

Rectangle {
    id: simpleButton

    property color buttonColor: "lightblue"
    property color borderColor: "transparent"
    property color hoverColor: "lightsteelblue"

    property string label
    property color labelColor: "black"
    property int labelSize: 14

    border.width: 2
    border.color: borderColor

    antialiasing: true
    radius: 10

    Text {
        id: buttonLabel

        anchors.centerIn: parent
        color: labelColor
        text: label
        font.pointSize: labelSize
    }

    signal buttonLeftClicked

    MouseArea {
        id: buttonMouseArea

        anchors.fill: parent
        hoverEnabled: true

        onClicked: buttonLeftClicked()
        onEntered: parent.border.color = hoverColor
        onExited: parent.border.color = borderColor
    }

    color: buttonMouseArea.pressed ? Qt.darker(buttonColor, 1.5) : buttonColor
    Behavior on color {
        ColorAnimation {
            duration: 50
        }
    }

    scale: buttonMouseArea.pressed ? 1.02 : 1.0
    Behavior on scale {
        NumberAnimation {
            duration: 50
        }
    }

}
