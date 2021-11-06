import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ColumnLayout {
    id: root

    signal clearClicked
    signal resetModelClicked
    signal loadModelClicked
    signal trainModelClicked
    signal saveModelClicked

    property int buttonWidth: 120
    property int buttonHeight: 30

    spacing: 20

    RowLayout {
        Layout.alignment: Qt.AlignHCenter
        spacing: root.spacing

        Button {
            id: clear

            Layout.preferredWidth: root.buttonWidth
            Layout.preferredHeight: root.buttonHeight

            flat: true
            highlighted: true
            text: "Clear"

            onClicked: {
                root.clearClicked()
            }
        }

        Button {
            id: resetModel

            Layout.preferredWidth: root.buttonWidth
            Layout.preferredHeight: root.buttonHeight

            flat: true
            highlighted: true
            text: "Reset model"

            onClicked: {
                root.resetModelClicked()
            }
        }
    }

    RowLayout {
        Layout.alignment: Qt.AlignHCenter
        spacing: root.spacing

        Button {
            id: loadModel

            Layout.preferredWidth: root.buttonWidth
            Layout.preferredHeight: root.buttonHeight

            flat: true
            highlighted: true
            text: "Load model"

            onClicked: {
                root.loadModelClicked()
            }
        }

        Button {
            id: trainModel

            Layout.preferredWidth: root.buttonWidth
            Layout.preferredHeight: root.buttonHeight

            flat: true
            highlighted: true
            text: "Train model"

            onClicked: {
                root.trainModelClicked()
            }
        }

        Button {
            id: saveModel

            Layout.preferredWidth: root.buttonWidth
            Layout.preferredHeight: root.buttonHeight

            flat: true
            highlighted: true
            text: "Save model"

            onClicked: {
                root.saveModelClicked()
            }
        }
    }
}
