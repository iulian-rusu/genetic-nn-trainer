import QtQuick

Canvas {
    id: root

    width: implicitWidth
    height: implicitHeight
    implicitWidth: scale * columns
    implicitHeight: scale * rows
    antialiasing: true

    // Color with 1.0 always
    property bool fullPrecision: false
    // Color at the cursor position
    property double peakIntensity: 0.5

    property bool erasing: false
    property bool spread: true

    property int columns: 28
    property int rows: 28
    property int scale: 10

    property color backgroundFill: "#000000"
    property color fillStyle: "#FFFFFF"
    property color pointerStyle: "#999999"

    property var grid: Array(rows).fill().map(() => Array(columns).fill(0.0))
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
                    ctx.fillStyle = `rgba(255, 255, 255, ${grid[i][j]})`;
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
            ctx.fillStyle = erasing ? root.backgroundFill : root.pointerStyle
            if (spread) {
                ctx.fillRect(
                    (root.currentPoint.x - 1) * root.scale,
                    (root.currentPoint.y - 1) * root.scale,
                    root.scale * 3,
                    root.scale * 3
                );
            }
            else {
                ctx.fillRect(
                    root.currentPoint.x * root.scale,
                    root.currentPoint.y * root.scale,
                    root.scale,
                    root.scale
                );
            }

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
               if (erasing) {
                   erase(mouseRow, mouseColumn);
               }
               else if (spread) {
                   spreadPaint(mouseRow, mouseColumn);
               }
               else {
                   precisePaint(mouseRow, mouseColumn);
               }
            }
            root.requestPaint();
        }

        onExited: {
            root.currentPoint = null;
            root.requestPaint();
        }
    }

    function clear() {
        grid = Array(rows).fill().map(() => Array(columns).fill(0.0));
        root.requestPaint();
    }

    function erase(mouseRow, mouseColumn) {
        root.grid[mouseRow][mouseColumn] = 0.0;
    }

    function randomOffset() {
        return 0.1 - Math.random() / 5;
    }

    function precisePaint(mouseRow, mouseColumn) {
        if (fullPrecision)
            root.grid[mouseRow][mouseColumn] = 1.0;
        else
            root.grid[mouseRow][mouseColumn] += peakIntensity + randomOffset();

        if (root.grid[mouseRow][mouseColumn] > 1.0) {
            root.grid[mouseRow][mouseColumn] = 1.0
        }
    }

    function spreadPaint(mouseRow, mouseColumn) {
        let intensity = peakIntensity;
        for (let i = -1; i <= 1; ++i)
            for (let j = -1; j <= 1; ++j) {
                let newRow = mouseRow + i;
                let newColumn = mouseColumn + j;
                if (newRow >= 0 && newRow < root.rows && newColumn >= 0 && newColumn < root.columns) {
                    let scale = 1 + Math.abs(i) * 2 + Math.abs(j) * 2;
                    root.grid[newRow][newColumn] += intensity / scale + randomOffset();
                    if (root.grid[newRow][newColumn] > 1.0) {
                        root.grid[newRow][newColumn] = 1.0
                    }
                }
            }
    }
}
