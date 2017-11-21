import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 480
    height: 320

    visibility: "FullScreen"

    color: "lightblue"

    opacity: 0.8

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        text: qsTr("Hello World!")
        anchors.centerIn: parent
    }

    Rectangle {
        anchors.fill: parent

        Item {
            id: rectangleGroup
            Rectangle {
                x: 100
                y: 50
                width: 100
                height: 100

                rotation: 90

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#FFFFFF" }
                    GradientStop { position: 0.5; color: "#000000" }
                    GradientStop { position: 1.0; color: "#FFFFFF" }
                }

                z: 1
            }

            Rectangle {
                x: 150
                y: 100
                width: 150
                height: 150

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#FF0000" }
                    GradientStop { position: 0.5; color: "#00FF00" }
                    GradientStop { position: 1.0; color: "#0000FF" }
                }

                z: 0.5
            }
        }

        Component.onCompleted: {
            for (var i = 0; i < rectangleGroup.children.length; i++) {
                console.log("x=", rectangleGroup.children[i].x);
            }
        }

    }

}

