import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("05Event")


    Text {
        id: greetingText
        text: qsTr("Hello World!")
        font.bold: true
        font.pointSize: 30
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        color: "red"
    }

    Text {
        id: greetingText2
        text: qsTr("Hello World2!")
        font.bold: true
        font.pointSize: 30
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: greetingText.bottom
        anchors.topMargin: 40
        color: "blue"

        function colorPicked(clr) {
            greetingText2.color = clr
        }
    }

    Component {
        id: colorPickerComponent
        Rectangle {
            signal colorPicked(color clr)
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    colorPicked(parent.color)
                }
            }
        }
    }

    Loader {
        id: redLoader
        width: 50
        height: 50
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 30
        anchors.bottomMargin: 30
        sourceComponent: colorPickerComponent

        onLoaded: {
            item.color = "red"
        }
    }

    Loader {
        id: blueLoader
        width: 50
        height: 50
        anchors.left: redLoader.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 30
        anchors.bottomMargin: 30
        sourceComponent: colorPickerComponent

        onLoaded: {
            item.color = "blue"
        }
    }

    Loader {
        id: blackLoader
        width: 50
        height: 50
        anchors.left: blueLoader.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 30
        anchors.bottomMargin: 30
        sourceComponent: colorPickerComponent

        onLoaded: {
            item.color = "black"
        }
    }

    Connections {
        target: redLoader.item
        onColorPicked: {
            greetingText.color = clr
        }
    }

    Connections {
        target: blueLoader.item
        onColorPicked: {
            greetingText.color = clr
        }
    }
}





