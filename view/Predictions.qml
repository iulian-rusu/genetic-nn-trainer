import QtQuick
import QtQuick.Controls

Label {
    id: root

    property var predictions: Array(10).fill(0)

    color: "#000000"
    text: `Predictions:\n` +
        ` [ 0 - ${predictions[0].toFixed(2).length > 5 ? "" : " "}${predictions[0].toFixed(2).length > 4 ? "" : "0"}${predictions[0].toFixed(2)} ]` +
        ` [ 1 - ${predictions[1].toFixed(2).length > 5 ? "" : " "}${predictions[1].toFixed(2).length > 4 ? "" : "0"}${predictions[1].toFixed(2)} ]` +
        ` [ 2 - ${predictions[2].toFixed(2).length > 5 ? "" : " "}${predictions[2].toFixed(2).length > 4 ? "" : "0"}${predictions[2].toFixed(2)} ]` +
        ` [ 3 - ${predictions[3].toFixed(2).length > 5 ? "" : " "}${predictions[3].toFixed(2).length > 4 ? "" : "0"}${predictions[3].toFixed(2)} ]` +
        ` [ 4 - ${predictions[4].toFixed(2).length > 5 ? "" : " "}${predictions[4].toFixed(2).length > 4 ? "" : "0"}${predictions[4].toFixed(2)} ]\n` +
        ` [ 5 - ${predictions[5].toFixed(2).length > 5 ? "" : " "}${predictions[5].toFixed(2).length > 4 ? "" : "0"}${predictions[5].toFixed(2)} ]` +
        ` [ 6 - ${predictions[6].toFixed(2).length > 5 ? "" : " "}${predictions[6].toFixed(2).length > 4 ? "" : "0"}${predictions[6].toFixed(2)} ]` +
        ` [ 7 - ${predictions[7].toFixed(2).length > 5 ? "" : " "}${predictions[7].toFixed(2).length > 4 ? "" : "0"}${predictions[7].toFixed(2)} ]` +
        ` [ 8 - ${predictions[8].toFixed(2).length > 5 ? "" : " "}${predictions[8].toFixed(2).length > 4 ? "" : "0"}${predictions[8].toFixed(2)} ]` +
        ` [ 9 - ${predictions[9].toFixed(2).length > 5 ? "" : " "}${predictions[9].toFixed(2).length > 4 ? "" : "0"}${predictions[9].toFixed(2)} ]`
}
