import QtQuick 2.6
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480

//    SimpleButton {
//        anchors.centerIn: parent
//        width: 480
//        height: 320
//        label: "Button"

//        onButtonLeftClicked: {
//            console.log("click")
//        }
//    }

    HelloWorldArea {
        anchors.fill: parent
    }
}
