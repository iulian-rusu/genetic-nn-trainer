import QtQuick

Canvas {
    id: root
    width: implicitWidth
    height: implicitHeight
    implicitWidth: scale * columns
    implicitHeight: scale * rows
    antialiasing: true

    property bool erasing: false
    property bool spread: true

    property int columns: 28
    property int rows: 28
    property int scale: 10

    property color backgroundFill: "#000000"
    property color fillStyle: "#FFFFFF"

    property var grid: Array(rows).fill().map(() => Array(columns).fill(false))
    property var currentPoint: null

    onPaint: {
        let ctx = getContext("2d");
        ctx.save();

        ctx.fillStyle = root.backgroundFill;
        ctx.fillRect(0, 0, root.width, root.height);

        ctx.fillStyle = root.fillStyle;

        for (let i = 0; i < grid.length; ++i) {
            for (let j = 0; j < grid[i].length; ++j) {
                if (grid[i][j]) {
                    ctx.fillRect(
                        j * root.scale,
                        i * root.scale,
                        root.scale,
                        root.scale
                    );
                }
            }
        }

        if (currentPoint) {
            ctx.fillRect(
                root.currentPoint.x * root.scale,
                root.currentPoint.y * root.scale,
                root.scale,
                root.scale
            );
        }

        ctx.restore();
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onPositionChanged: (mouse) => {
            if (!containsMouse)
                return;

            let mouseColumn = Math.floor(mouse.x / root.scale);
            let mouseRow    = Math.floor(mouse.y / root.scale);
            root.currentPoint = {"x": mouseColumn, "y": mouseRow};
            if (pressed) {
                root.grid[mouseRow][mouseColumn] = true;
            }
            root.requestPaint();
        }

        onExited: {
            root.currentPoint = null;
            root.requestPaint();
        }
    }

    function clear() {
        grid = Array(rows).fill().map(() => Array(columns).fill(false));
        root.requestPaint();

        console.log(erasing);
        console.log(spread);
    }
}
