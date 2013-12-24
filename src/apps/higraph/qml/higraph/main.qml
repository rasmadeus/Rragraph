import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQml.Models 2.1
import QtQuick.Dialogs 1.0
import "help"
import "histogram"

Rectangle {
    objectName: "root"
    function getUrls(){
        return fileDialog.fileUrls
    }


    width: 800
    height: 700

    signal pathsArePrepared()
    FileDialog{
        id: fileDialog
        visible: false
        selectMultiple: true
        title: qsTr("Укажите файлы-данные")
        nameFilters:["Текстовые файлы(*.txt)", "Все файлы(*)"]
        onAccepted:{
            pathsArePrepared()
        }
    }


    ObjectModel{
       objectName: "windowsModel"
       id: itemModel
       Histogram{
           id: histogram
           objectName: "histogram"
           width: view.width
           height: view.height
       }
       Help{
           width: view.width
           height: view.height
       }
    }

    ListView {
        id: view
        anchors.fill: parent
        model: itemModel
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem; flickDeceleration: 1000
        cacheBuffer: 200
    }

    signal closeAllFiles()
    RowLayout{
        id: menu
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10
        anchors.bottomMargin: 10
        ImageButton{
            source: "qrc:/res/menu/close.png"
            visible: view.currentIndex == 0
            onTriggered: {
                histogram.clear()
                closeAllFiles()
            }
        }
        ImageButton{
            source: "qrc:/res/menu/plus.png"
            visible: view.currentIndex == 0
            onTriggered: fileDialog.visible = true
        }
        ImageButton{
            source: "qrc:/res/menu/histogram.png"
            onTriggered: view.currentIndex = 0
        }
        ImageButton{
            source: "qrc:/res/menu/help.png"
            onTriggered: view.currentIndex = 1
        }
    }

}
