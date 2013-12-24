import QtQuick 2.0
import "../"
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

ContentBackground{
    id: histogram
    mainColor: "#dfd"

    function getMinRang(){
        return 0.01 * maxValueRanger.value
    }

    function getRearrangedValue(value){
        if (value < 0){
            value *= -1
        }
        var range = getMinRang()
        if(value < range){
            value = range
        }
        return value
    }

    function insert(index, value){
        model.insert(index, {"value": getRearrangedValue(value)})
    }

    function append(){
        model.append({"value":  getRearrangedValue(0)})
    }

    function setValue(i, value){
        model.get(i).value = getRearrangedValue(value)
    }

    function clear(){        
        model.clear()
        mover.value = 0
        mover.maximumValue = 0
    }

    function getDelegateHeight(value){
        var res = maxValueRanger.value === 0 ? view.height : getRearrangedValue(value) / maxValueRanger.value * view.height
        return res > view.height ? view.height : res
    }

    function getDelegateWidth(){
        return view.width / model.count
    }

    ListModel{
        id: model
        objectName: "histograModel"
    }

    Component{
        id: delegate
        ContentBackground{
            y: view.height - height
            mainColor: Qt.rgba(Math.random(255), Math.random(255), Math.random(255));
            secondColor: histogram.mainColor
            id: delegateBody
            width: getDelegateWidth()
            height: getDelegateHeight(value)
        }
    }

    ListView{
        id: view
        anchors.fill: parent
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.topMargin: 5
        keyNavigationWraps: true
        model: model
        delegate: delegate
        orientation: ListView.Horizontal
    }


    Text{
        anchors.top: parent.top
        anchors.right: parent.horizontalCenter
        anchors.topMargin: 10
        anchors.rightMargin: 20
        property double currentFileTime: 0
        id: firstFileTime
        objectName: "firstFileTime"
        text: qsTr("t = ") + currentFileTime
        color: "#2c6d0c"
        font.pointSize: 15
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Text{
        anchors.top: parent.top
        anchors.left: parent.horizontalCenter
        anchors.topMargin: 10
        property double currentSliceMaxValue: 0
        id: sliceMaxValue
        objectName: "sliceMaxValue"
        text: qsTr("max = ") + currentSliceMaxValue
        color: "#2c6d0c"
        font.pointSize: 15
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    signal moverPosWasChanged()
    Slider{
        id: mover
        objectName: "mover"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.bottomMargin: 0
        minimumValue: 0
        maximumValue: 0
        stepSize: 1
        width: 350
        height: 30
        updateValueWhileDragging: true
        onValueChanged: moverPosWasChanged()
    }

    Row{
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 10
        anchors.bottomMargin: 0
        spacing: 5
        Text{
            color: "#27a217"
            text: qsTr("Относительная высота экрана")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            height: 26
        }

        Slider{
            id: maxValueRanger
            minimumValue: 0
            maximumValue: 100
            value: 3
            stepSize: 1
            width: 200
            height: 30
            updateValueWhileDragging: true
        }
    }
}
