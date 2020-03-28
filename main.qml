import QtQuick 2.12
import QtQuick.Controls 2.5
import GridGestureGUI 1.0
import ScreenShot 1.0
import "const.js" as CONST

//アプリケーションウィンドウを定義
ApplicationWindow {
    visible: true
    width: CONST.GRIDWINDOW_WIDTH
    height: CONST.GRIDWINDOW_HEIGHT
    title: qsTr("Test Grid")

    id: root
    color: "white"

    //グリッドを配置
    Grid {
        id: dropGrid
        anchors.fill: parent
        anchors.margins: 5
        columns: CONST.GRIDWINDOW_WIDTH / CONST.GRID_WIDTH

        //リターンキー押下なら、スクリーンショット保存
        ScreenShot {
            id: screenshot
        }
        //フォーカスを設定する
        focus: true
        Keys.onReturnPressed: screenshot.save()

        Repeater {
            model: CONST.GRIDWINDOW_HEIGHT / CONST.GRID_HEIGHT * dropGrid.columns
            Rectangle {
                id: dropRect
                width: CONST.GRID_WIDTH
                height: CONST.GRID_HEIGHT
                radius: 4
                opacity: 1.0
                states: State {
                    //ドラッグ状態で領域内にいたら背景色を変更
                    when: imageDropArea.containsDrag
                    PropertyChanges { target: dropRect; opacity: 0.5 }
                }
                //ドロップの受付
                DropArea {
                    id: imageDropArea
                    anchors.fill: parent
                    GridGestureGUI {
                        id: gridGestureGUI
                        anchors.fill: parent
                    }
                    onEntered: {
                        gridGestureGUI.setPattern0000(true)
                        gridGestureGUI.seekPatternMap(drag.x, drag.y)
                    }
                    onExited: {
                        gridGestureGUI.setPattern0000(false)
                    }
                    onPositionChanged: {
                        gridGestureGUI.seekPatternMap(drag.x, drag.y)
                    }
                    onDropped: {
                        if(drop.hasUrls) {
                            // drop.urls[0]だけComponent(Image)を生成(複数ドラッグ&ドロップは未対応)
                            if(drop.urls[0].indexOf(".bmp") >= 0
                            || drop.urls[0].indexOf(".png") >= 0
                            || drop.urls[0].indexOf(".jpg") >= 0) {
                                //Component(Image)を生成
                                var component = Qt.createComponent("gridPartsImage.qml")
                                var object = component.createObject(gridGestureGUI)
                                object.source = drop.urls[0]
                                if(object.implicitWidth >= object.implicitHeight) {
                                    dropComponent(object)
                                }else {
                                    dropComponent(object)
                                    object.source.x += object.source.height - object.source.width/2
                                }
                            }
                        }else if(drop.source.objectName === "imageConponent") {
                            //ドラッグ&ドロップ済のimageConponentを再ドロップした場合
                            drop.source.state = "Drop"
                            dropComponent(drop.source)
                        }
                    }

                    //グリッドにドロップした時の処理(objectのx,y座標、横幅、高さを取得)
                    function dropComponent(object) {
                        //共通の処理
                        object.parent = gridGestureGUI
                        object.x = gridGestureGUI.getNextXX()
                        object.y = gridGestureGUI.getNextYY()
                        //Componet(Image)の原画像の幅が高さより、大きい場合の処理
                        if(object.implicitWidth >= object.implicitHeight) {
                            object.width = gridGestureGUI.getNextWW()
                            object.height = gridGestureGUI.getNextHH()
                        //Componet(Image)の原画像の幅が高さより、小さい場合の処理
                        }else {
                            //widthとhedightの値は交換する
                            object.width = gridGestureGUI.getNextHH()
                            object.height = gridGestureGUI.getNextWW()
                            //回転処理
                            object.originX = object.height/2
                            object.originY = object.height/2
                            object.originAngle = 90
                        }
                        //共通の処理
                        gridGestureGUI.setPattern0000(false)
                    }
                }
            }
        }
    }
}

