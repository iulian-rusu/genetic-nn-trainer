import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Button {
    id: root

    width: implicitWidth
    height: implicitHeight

    flat: true
    highlighted: true

    property color backgroundColorNormal: "#3BA55D"
    property color backgroundColorHovered: "#349252"
    property color backgroundColorPressed: "#349252"
    property color backgroundColorDisabled: "#444444"

    property color borderColorNormal: "#3BA55D"
    property color borderColorHovered: "#349252"
    property color borderColorPressed: "#349252"
    property color borderColorDisabled: "#000000"

    property color textColorNormal: "#ffffff"
    property color textColorHovered: "#ffffff"
    property color textColorPressed: "#ffffff"
    property color textColorDisabled: "#888888"

    property real radius: 5
    property int borderWidth: 1
    padding: 5

    // property string textFontFamily: DiscodeFont.regularFont.name
    property real textPointSize: 12
    property bool bold: false
    property bool italic: false
    text: "Placeholder"

    property alias aspectRatio: iconContent.aspectRatio
    property real iconWidth: iconHeight * aspectRatio
    property real iconHeight: 24

    property string iconSourceNormal: ""
    property string iconSourceHovered: iconSourceNormal
    property string iconSourcePressed: iconSourceNormal
    property string iconSourceDisabled: iconSourceNormal

    property bool textVisible: true
    property int textColumn: 1
    property int textRow: 0
    property bool iconVisible: false
    property int iconColumn: 0
    property int iconRow: 0

    background: Rectangle {
        id: buttonBackground

        anchors.fill: parent

        radius: root.radius
        border.width: root.borderWidth

        color: !root.enabled ? root.backgroundColorDisabled :
                                 root.pressed ? root.backgroundColorPressed :
                                           root.hovered ? root.backgroundColorHovered :
                                                     root.backgroundColorNormal

        border.color: !root.enabled ? root.borderColorDisabled :
                                 root.pressed ? root.borderColorPressed :
                                           root.hovered ? root.borderColorHovered :
                                                     root.borderColorNormal
    }

    contentItem: GridLayout {
        id: contentLayout

        rows: 2
        columns: 2

        Text {
            id: textContent

            visible: root.textVisible

            Layout.column: root.textColumn
            Layout.row: root.textRow
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            color: !root.enabled ? root.textColorDisabled :
                                     root.pressed ? root.textColorPressed :
                                               root.hovered ? root.textColorHovered :
                                                         root.textColorNormal

            // font.family: root.textFontFamily
            font.pointSize: root.textPointSize
            font.bold: root.bold
            font.italic: root.italic

            text: root.text
        }

        Image {
            id: iconContent

            visible: root.iconVisible

            Layout.column: root.iconColumn
            Layout.row: root.iconRow
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            Layout.preferredWidth: root.iconWidth
            Layout.preferredHeight: root.iconHeight

            fillMode: Image.PreserveAspectFit
            property real aspectRatio: sourceSize.width / sourceSize.height

            source: !root.enabled ? root.iconSourceDisabled :
                                     root.pressed ? root.iconSourcePressed :
                                               root.hovered ? root.iconSourceHovered :
                                                         root.iconSourceNormal
        }
    }
}
