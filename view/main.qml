import QtQuick
import QtQuick.Layouts
import QtQuick.Window

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: "Genetic nn trainer"

    ColumnLayout {
        id: columnLayout

        anchors.centerIn: parent
        spacing: 15

        VCanvas {
            id: canvas
            Layout.alignment: Qt.AlignHCenter

            Connections {
                target: buttons
                function onClearClicked() {
                    canvas.clear();
                }
            }
        }

        Predictions {
            id: predictions
            Layout.alignment: Qt.AlignHCenter

        }

        Stats {
            id: stats
            Layout.alignment: Qt.AlignHCenter

        }

        Buttons {
            id: buttons
            Layout.alignment: Qt.AlignHCenter

        }
    }

    Timer {
        id: timer
        interval: 1000
        repeat: true

        Component.onCompleted: {
            timer.start()
        }
    }
}
