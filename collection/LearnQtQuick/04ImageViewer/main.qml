import QtQuick 2.6
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.2

Window {
    visible: true

    minimumWidth: 600
    minimumHeight: 480

    title: qsTr("ImageViewer")

    BusyIndicator {
        id: busyIndicator
        running: false;
        visible: false;

        anchors.centerIn: imageViewer
    }

    Text {
        id: errorText
        visible: false;
        text: qsTr("Load Failed!")
        anchors.centerIn: imageViewer
        font.pointSize: 30
        font.bold: true
        color: "red"
    }

    Image {
        id: imageViewer
//        source: "file"

        anchors.fill: parent
        asynchronous: true
        fillMode: Image.PreserveAspectFit

        onStatusChanged: {
            if (status == Image.Ready) {
                busyIndicator.running = false;
                busyIndicator.visible = false;
                errorText.visible = false;
            } else if (status == Image.Loading) {
              busyIndicator.running = true;
              busyIndicator.visible = true;
              errorText.visible = false;
            } else if (status == Image.Error) {
              errorText.visible = true;
            }
        }
    }

    Button {
        id: openButton
        text: qsTr("Open")

        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.topMargin: 5
        anchors.bottomMargin: 5

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 80
                implicitHeight: 30
                color: control.hovered ? "lightblue" : "white"
                border.width: control.pressed ? 2 : 1
                border.color: (control.hovered || control.pressed) ? "green" : "#888888"

                radius: 10
                antialiasing: true
            }
        }

        onClicked: {
            fileDialogLoader.item.open()
        }
    }

    Text {
        id: pathText
        text: qsTr("image path")

        anchors.leftMargin: 10
        anchors.bottomMargin: 5
        anchors.verticalCenter: openButton.verticalCenter
        anchors.left: openButton.right

        font.pointSize: 10
    }


    Connections {
        target: fileDialogLoader.item
        onPathAccepted: {
            imageViewer.source = path;
            pathText.text = path;
        }
    }

    Loader {
        id: fileDialogLoader
        sourceComponent: fileDialogComponent
    }

    Component {
        id: fileDialogComponent
        FileDialog {
            id: fileDialog

            title: qsTr("Please choose a file")
            nameFilters: ["Image files (*.jpg *.png *.bmp)"]
            modality: Qt.WindowModal

            signal pathAccepted(string path)

            onAccepted: {
//                imageViewer.source = fileUrl;
//                pathText.text = fileUrl;
                pathAccepted(fileUrl)
            }
        }
    }

}





















