import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 1.0

GridLayout {
    id: root

    property int generations: 0
    property double accuracy: 0

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
        id: accuracyLabel
        color: "#000000"
        text: `Accuracy: ${accuracy.toFixed(2).length > 5 ? "" : " "}${accuracy.toFixed(2).length > 4 ? "" : "0"}${accuracy.toFixed(2)}%`
    }

    Connections {
        target: model
        function onUpdateTrainData(new_generations, new_accuracy) {
            generations = new_generations
            accuracy = new_accuracy
        }
    }
}
