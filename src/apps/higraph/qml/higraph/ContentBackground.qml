import QtQuick 2.0

Rectangle {
    property color mainColor: "#000"
    property color secondColor: "#fff"
    gradient: Gradient {
        GradientStop{
            position: 1
            color: secondColor
        }
        GradientStop{
            position: 0
            color: mainColor
        }
    }
}
