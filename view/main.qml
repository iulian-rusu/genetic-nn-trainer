import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Dialogs

Window {
    id: root
    width: 640
    height: 560
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

            Connections {
                target: timer
                function onTriggered() {
                    controller.onUpdateModel(canvas.grid)
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

    FileDialog {
        id: loadModelDialog

        modality: Qt.ApplicationModal
        fileMode: FileDialog.OpenFile

        onAccepted: {
            controller.onLoadModel(fileDialog.selectedFile);
        }

        Connections {
            target: buttons
            function onLoadModelClicked() {
                loadModelDialog.open();
            }
        }
    }

    FileDialog {
        id: saveModelDialog

        modality: Qt.ApplicationModal
        fileMode: FileDialog.SaveFile

        onAccepted: {
            controller.onSaveModel(fileDialog.selectedFile);
        }

        Connections {
            target: buttons
            function onSaveModelClicked() {
                saveModelDialog.open()
            }
        }
    }
}
