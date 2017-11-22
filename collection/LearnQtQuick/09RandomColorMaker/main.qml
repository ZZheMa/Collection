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

    Rectangle {
        id: colorRect
        width: 200
        height: 200
        anchors.centerIn: parent
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

    Button {
        id: algotithmButton
        anchors.left: stopButton.right
        anchors.bottom: parent.bottom
        onClicked: {
            var algorithm = randomColorMaker.colorAlgorithm();
            algorithm = (algorithm + 1) % RandomColorMaker.RandomColorCount;
            randomColorMaker.setColorAlgorithm(algorithm);
            text = convertColorAlgorithmToString(algorithm);
        }
    }

    function convertColorAlgorithmToString(randomColorAlgorithm) {
        if (randomColorAlgorithm === RandomColorMaker.RandomColorRed) {
            return qsTr("RandomRed");
        } else if (randomColorAlgorithm === RandomColorMaker.RandomColorGreen) {
            return qsTr("RandomGreen");
        } else if (randomColorAlgorithm === RandomColorMaker.RandomColorBlue) {
            return qsTr("RandomBlue");
        } else if (randomColorAlgorithm === RandomColorMaker.RandomColorRgb) {
            return qsTr("RandomRGB");
        } else if (randomColorAlgorithm === RandomColorMaker.RandomColorLinearIncrease) {
            return qsTr("RandomLinearIncrease");
        }
    }

    Component.onCompleted: {
        randomColorMaker.color = "black"
        algotithmButton.text = convertColorAlgorithmToString(randomColorMaker.colorAlgorithm())
    }

    Connections {
        target: randomColorMaker
        onColorChanged: {
            colorRect.color = color
        }

        onCurrentTimeNotified: {
            currentDateTimeText.text = time
            currentDateTimeText.color = randomColorMaker.timeColor;
        }
    }

    Connections {
        target: randomColorMaker
    }
}
