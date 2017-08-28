import QtQuick 2.0

Rectangle {
    id: helloWorldArea

    property color textColor: "black"

    Text {
        id: helloText
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Hello World!"
        color: textColor
        font.bold: true
        font.pointSize: 30
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    states: State {
        name: "down"
        when: mouseArea.pressed
        PropertyChanges {
            target: helloText
            y: 160
            rotation: 180
            color: "red"
        }
    }

    transitions: Transition {
        from: ""
        to: "down"
        reversible: true
        ParallelAnimation {
            ColorAnimation {
                duration: 500
            }

            NumberAnimation {
                properties: "y,rotation"
                duration: 500
                easing.type: Easing.InOutSine
            }
        }
    }

    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: helloText.bottom
        anchors.topMargin: 100
        rows: 2
        columns: 3
        spacing: 5

        Cell { cellColor: "red"; onMouseLeftClicked: textColor = cellColor; }
        Cell { cellColor: "green"; onMouseLeftClicked: textColor = cellColor; }
        Cell { cellColor: "blue"; onMouseLeftClicked: textColor = cellColor; }
        Cell { cellColor: "cyan"; onMouseLeftClicked: textColor = cellColor; }
        Cell { cellColor: "magenta"; onMouseLeftClicked: textColor = cellColor; }
        Cell { cellColor: "black"; onMouseLeftClicked: textColor = cellColor; }
    }

}
