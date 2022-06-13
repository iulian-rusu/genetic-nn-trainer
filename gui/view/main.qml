import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Window

Window {
    id: root
    width: 720
    height: 640
    visible: true
    title: "Genetic nn trainer"

    color: "#ffffff"

    ColumnLayout {
        id: columnLayout

        anchors.centerIn: parent
        spacing: 15

        VCanvas {
            id: canvas
            Layout.alignment: Qt.AlignHCenter

            erasing: brushes.erasing
            spread: brushes.spread

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

        Brushes {
            id: brushes
            Layout.alignment: Qt.AlignHCenter
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

            trainModel: () => {
                controller.onTrainModel(canvas.grid)
            }
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
            controller.onLoadModel(loadModelDialog.selectedFile);
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
            controller.onSaveModel(saveModelDialog.selectedFile);
        }

        Connections {
            target: buttons
            function onSaveModelClicked() {
                saveModelDialog.open()
            }
        }
    }

    Popup {
        id: popup
        anchors.centerIn: parent
        padding: 20
        modal: true
        dim: true

        ColumnLayout {
            spacing: 20
            Label {
                id: popupLabel
                Layout.alignment: Qt.AlignHCenter
                color: "#FFFFFF"
            }
            Button {
                id: popupButton
                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 80
                Layout.preferredHeight: 25
                text: "Ok"
                onClicked: popup.close()
            }
        }

        Connections {
            target: model
            function onShowPopup(text) {
                popupLabel.text = text
                popup.open()
            }
        }
    }
}
