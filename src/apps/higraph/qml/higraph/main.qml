import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQml.Models 2.1
import "data"
import "help"

Rectangle {
    objectName: "root"

    width: 500
    height: 500

    RowLayout{
        id: menu
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10
        anchors.topMargin: 10
        ImageButton{
            source: "qrc:/res/menu/plus.png"
            onTriggered:  view.currentIndex = 0
        }
        ImageButton{
            source: "qrc:/res/menu/histogram.png"
            onTriggered: view.currentIndex = 1
        }
        ImageButton{
            source: "qrc:/res/menu/help.png"
            onTriggered: view.currentIndex = 2
        }
    }

    ObjectModel{
       objectName: "windowsModel"
       id: itemModel
       Data{
           objectName: "data"
           width: view.width
           height: view.height
       }
       Rectangle{
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
        anchors.topMargin: menu.height + 20
        model: itemModel
        preferredHighlightBegin: 0; preferredHighlightEnd: 0
        highlightRangeMode: ListView.StrictlyEnforceRange
        orientation: ListView.Horizontal
        snapMode: ListView.SnapOneItem; flickDeceleration: 1000
        cacheBuffer: 200
    }

}
