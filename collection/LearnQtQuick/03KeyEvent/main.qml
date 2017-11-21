import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Key Event Demo")


    Rectangle {
        anchors.fill: parent
        focus: true
        color: "lightblue"

        Keys.enabled: true

        Keys.onDeletePressed: {
            Qt.quit();
        }

        Keys.onEscapePressed: {
            Qt.quit();
        }

        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_0:
            case Qt.Key_1:
            case Qt.Key_2:
            case Qt.Key_3:
            case Qt.Key_4:
            case Qt.Key_5:
            case Qt.Key_6:
            case Qt.Key_7:
            case Qt.Key_8:
            case Qt.Key_9:
                event.accepted = true;
                keyEventText.text = event.key - Qt.Key_0
                break;
            default:
                break;
            }

        }

        Text {
            id: keyEventText

            font.bold: true
            font.pointSize: 24

            color: "red"

            text: qsTr("Start...");
            anchors.centerIn: parent
        }

    }
 }
