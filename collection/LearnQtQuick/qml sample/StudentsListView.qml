import QtQuick 2.0

Rectangle {
    id: studentsListView
    anchors.margins: 3

    Component {
        id: viewDelegate
        Rectangle {
            radius: 5
            border.width: 2
            border.color: "lightblue"

            anchors.left: parent.left
            anchors.right: parent.right
            height: column.implicitHeight + 8

            Column {
                id: column
                anchors.fill: parent
                anchors.margins: 2

                Text {
                    text: "Name: " + name
                }

                Text {
                    text: "Gender: " + gender
                }

                Text {
                    text: "Address: " + address
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
        spacing: 2

        delegate: viewDelegate
        model: StudentsListViewModel {}
        cacheBuffer: 30
    }

}
