import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.3

Window {
    visible: true
    width: 640
    height: 480

    Keys.enabled: true
    Keys.forwardTo: [keyField]

    Rectangle {
        id: timerField

        width: parent.width
        height: parent.height / 2
        color: "lightblue"

        anchors.left: parent.left
        anchors.top: parent.top

        QtObject {
            id: attrs
            property int counter
            Component.onCompleted: {
                counter = 10
            }
        }

        Text {
            id: countText
            font.bold: true
            font.pointSize: 30
            anchors.centerIn: parent
        }

        Timer {
            id: countTimer
            repeat: true
            interval: 1000
            triggeredOnStart: true

            onTriggered: {
                countText.text = attrs.counter
                countText.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1)

                attrs.counter -= 1
                if (attrs.counter < 0) {
                    stop()
                    countText.text = qsTr("Finished")
                }
            }
        }

        Button {
            id: startButton
            text: qsTr("Start")

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            onClicked: {
                attrs.counter = 10;
                countTimer.start();
            }
        }
    }


    Rectangle {
        id: keyField
        width: parent.width
        height: parent.height / 2
        color: "lightgray"

        anchors.left: parent.left
        anchors.top: timerField.bottom

        focus: true
        Keys.enabled: true

        Keys.forwardTo: [moveText]

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.MidButton | Qt.RightButton
            onClicked: {
                if (mouse.button === Qt.LeftButton) {
                    parent.color = "lightgray"
                } else if (mouse.button === Qt.RightButton) {
                    parent.color = "lightblue"
                } else if (mouse.button === Qt.MidButton) {
                    parent.color = "yellow"
                }

                moveText.x = mouse.x
                moveText.y = mouse.y
            }
            onDoubleClicked: {
                parent.color = Qt.rgba(Math.random(), Math.random(), Math.random(), 1)
            }
        }

        Text {
            id: moveText
            x: 0
            y: 0

            text: qsTr("Moving Text")
            font.bold: true
            font.pointSize: 20
            color: "blue"

            Keys.enabled: true
            Keys.onEscapePressed: {
                Qt.quit()
            }

            Keys.onPressed: {
                switch (event.key) {
                case Qt.Key_Left:
                    x -= 10;
                    break;
                 case Qt.Key_Right:
                    x += 10;
                    break;
                 case Qt.Key_Up:
                    y -= 10;
                    break;
                 case Qt.Key_Down:
                     y += 10;
                     break;
                 default:
                     break;
                }

                event.accepted = true;
            }

        }

    }
}
