import QtQuick 2.0

Image{
    signal triggered()
    MouseArea{
        id: mouse
        hoverEnabled: true
        anchors.fill: parent
        onClicked: triggered()
    }

    opacity: mouse.containsMouse ? 0 : 1
    Behavior on opacity{
        NumberAnimation{}
    }
}
