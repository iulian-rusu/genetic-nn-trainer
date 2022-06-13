import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 1.0

GridLayout {
    id: root

    property int generations: 0
    property double loss: 0
    property double train_accuracy: 0
    property double test_accuracy: 0

    columns: 2
    columnSpacing: 40
    rowSpacing: 15

    Label {
        id: titleLabel

        Layout.alignment: Qt.AlignHCenter
        Layout.columnSpan: 2

        color: "#000000"
        text: "Train data:"
    }

    Label {
        id: generationsLabel
        color: "#000000"
        text: `Generations: ${generations}`
    }

    Label {
        id: lossLabel
        color: "#000000"
        text: `Loss: ${loss.toFixed(2).length > 5 ? "" : " "}${loss.toFixed(2).length > 4 ? "" : "0"}${loss.toFixed(2)}`
    }

    Label {
        id: trainAccuracyLabel
        color: "#000000"
        text: `Train accuracy: ${train_accuracy.toFixed(2).length > 5 ? "" : " "}${train_accuracy.toFixed(2).length > 4 ? "" : "0"}${train_accuracy.toFixed(2)}%`
    }

    Label {
        id: testAccuracyLabel
        color: "#000000"
        text: `Test accuracy: ${test_accuracy.toFixed(2).length > 5 ? "" : " "}${test_accuracy.toFixed(2).length > 4 ? "" : "0"}${test_accuracy.toFixed(2)}%`
    }

    Connections {
        target: model
        function onUpdateTrainData(new_generations, new_loss, new_train_accuracy, new_test_accuracy) {
            generations = new_generations
            loss = new_loss
            train_accuracy = new_train_accuracy
            test_accuracy = new_test_accuracy
        }
    }
}
