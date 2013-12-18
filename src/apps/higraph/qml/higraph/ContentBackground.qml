import QtQuick 2.0

Rectangle {
    property color mainColor: "#000"
    gradient: Gradient {
        GradientStop{
            position: 0.0;
            color: "#fff";
        }
        GradientStop{
            position: 1.00;
            color: mainColor;
        }
    }
}
