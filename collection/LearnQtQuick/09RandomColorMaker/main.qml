import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import an.qt.RandomColorMaker 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("09RandomColorMaker")

    Text {
        id: currentDateTimeText
        text: qsTr("Current DateTime");
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
        font.pointSize: 30
        color: "blue"
    }

    RandomColorMaker {
        id: randomColorMaker
    }

    Button {
        id: startButton
        text: qsTr("Start")
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        onClicked: {
            randomColorMaker.start();
        }
    }

    Button {
        id: stopButton
        text: qsTr("Stop")
        anchors.left: startButton.right
        anchors.bottom: parent.bottom
        onClicked: {
            randomColorMaker.stop();
        }
    }

    Connections {
        target: randomColorMaker
        onColorChanged: {
            currentDateTimeText.color = color
        }

        onCurrentTimeNotified: {
            currentDateTimeText.text = time
        }
    }
}
