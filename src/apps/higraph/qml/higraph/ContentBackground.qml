import QtQuick 2.0

Rectangle {
    property color mainColor: "#000"
    property color secondColor: "#fff"
    property bool isRevert: false
    gradient: Gradient {
        GradientStop{
            position: isRevert ? 1 : 0;
            color: secondColor
        }
        GradientStop{
            position: isRevert ? 0 : 1;
            color: mainColor
        }
    }
}
