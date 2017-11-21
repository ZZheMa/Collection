import QtQuick 2.7
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("08Canvas")

    Canvas {
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")

            ctx.lineWidth = 2
            ctx.strokeStyle = "blue"
//            context.fillStyle = "red"

            var gradient = ctx.createLinearGradient(50, 50, 110, 70)
            gradient.addColorStop(0.0, Qt.rgba(0, 1, 0, 1))
            gradient.addColorStop(1.0, Qt.rgba(0, 0, 1, 1))
            ctx.fillStyle = gradient
            ctx.beginPath()
            ctx.rect(0, 0, 120, 80)
            ctx.fill()
            ctx.stroke()

//            var ctx = getContext("2d")

//               var gradient = ctx.createLinearGradient(100,0,100,200)
//               gradient.addColorStop(0, "blue")
//               gradient.addColorStop(0.5, "lightsteelblue")
//               ctx.fillStyle = gradient
//               ctx.fillRect(50,50,100,100)
        }
    }
}
