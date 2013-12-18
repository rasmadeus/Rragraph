import QtQuick 2.1
import QtQml.Models 2.1
import QtQuick.Dialogs 1.0
import "../"
import QtQuick.Controls 1.0

Rectangle{
    function getUrls(){
        return fileDialog.fileUrls
    }

    ContentBackground{
        anchors.fill: parent
        mainColor: "#bfb"
    }

    signal pathsArePrepared()
    FileDialog{
        id: fileDialog
        visible: false
        selectMultiple: true
        title: qsTr("Укажите файлы-данные")
        nameFilters:["Text files (*.txt)", "All files (*)"]
        onAccepted:{
            pathsArePrepared()
        }
    }
    ListModel{
        id: filesModel
    }
    ComboBox {
        id: filesList
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        width: 200
        model: filesModel
    }
    TableView{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: filesList.bottom
        smooth: true
        width: 200
        headerVisible: true
    }
    Text{
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        text: qsTr("Загрузить данные")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 10
        color: "#356f35"
        elide: Text.ElideMiddle
        MouseArea{
            id: mouse
            hoverEnabled: true
            anchors.fill: parent
            onClicked: fileDialog.visible = true
        }
        opacity: mouse.containsMouse ? 1 : 0
        Behavior on opacity{
            NumberAnimation{}
        }
    }
}
