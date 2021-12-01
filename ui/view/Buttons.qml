import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    id: root

    signal clearClicked
    signal loadModelClicked
    signal saveModelClicked

    property int buttonWidth: 120
    property int buttonHeight: 30

    property var trainModel: () => {}

    spacing: 20

    RowLayout {
        Layout.alignment: Qt.AlignHCenter
        spacing: root.spacing

        VButton {
            id: clear

            Layout.preferredWidth: root.buttonWidth
            Layout.preferredHeight: root.buttonHeight

            text: "Clear"

            onClicked: {
                root.clearClicked()
            }
        }

        VButton {
            id: resetModel

            Layout.preferredWidth: root.buttonWidth
            Layout.preferredHeight: root.buttonHeight

            text: "Reset model"

            onClicked: {
                controller.onResetModel()
            }
        }
    }

    RowLayout {
        Layout.alignment: Qt.AlignHCenter
        spacing: root.spacing

        VButton {
            id: loadModel

            Layout.preferredWidth: root.buttonWidth
            Layout.preferredHeight: root.buttonHeight

            text: "Load model"

            onClicked: {
                root.loadModelClicked()
            }
        }

        VButton {
            id: trainModel

            Layout.preferredWidth: root.buttonWidth
            Layout.preferredHeight: root.buttonHeight

            text: "Train model"

            onClicked: {
                //controller.onTrainModel()
                root.trainModel()
            }
        }

        VButton {
            id: saveModel

            Layout.preferredWidth: root.buttonWidth
            Layout.preferredHeight: root.buttonHeight

            text: "Save model"

            onClicked: {
                root.saveModelClicked()
            }
        }
    }
}
