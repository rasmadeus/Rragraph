import QtQuick 2.0

Image{
    property bool opacityAnimationIsActive: true
    signal triggered()
    MouseArea{
        id: mouse
        hoverEnabled: true
        anchors.fill: parent
        onClicked: triggered()
    }

    opacity: mouse.containsMouse ? !opacityAnimationIsActive : 1
    Behavior on opacity{
        NumberAnimation{}
    }
}
