import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    id: root

    property bool erasing: eraser.checked
    property bool spread: !eraser.checked && spread.checked

    spacing: 20

    VRadioButton {
        id: precise

        checked: true
        text: "Precise"
    }

    VRadioButton {
        id: spread

        text: "Spread"
    }

    VRadioButton {
        id: eraser

        text: "Eraser"
    }
}
