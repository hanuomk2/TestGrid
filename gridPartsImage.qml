import QtQuick 2.12
import QtQuick.Controls 2.5
import "const.js" as CONST

Image {
    id: imageConponent
    objectName: "imageConponent"
    width: CONST.GRID_WIDTH / 4
    height: CONST.GRID_HEIGHT / 4
    // fillMode: Image.PreserveAspectFit

    // 回転処理をalias定義
    transform: Rotation {
        id: originRotation
    }
    property alias originX: originRotation.origin.x
    property alias originY: originRotation.origin.y
    property alias originAngle: originRotation.angle

    Drag.active: mouseArea.drag.active
    // マウスカーソルの位置をhotSpotに設定
    Drag.hotSpot.x: mouseArea.mouseX
    Drag.hotSpot.y: mouseArea.mouseY

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        // ドラッグ&ドロップでドロップ(リリース)した場合
        onReleased: parent.Drag.drop()
    }

    states: [
        State {
            name: "Drag"
            when: mouseArea.drag.active
            PropertyChanges { target: imageConponent; opacity: 0.5 }
        },
        State {
            name: "Drop"
            PropertyChanges { target: imageConponent; opacity: 1.0 }
        }
    ]
}
