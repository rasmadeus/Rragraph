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
        try{
            model.get(i).value = getRearrangedValue(value)
        }
        catch(error){
        }
     }

    function clear(){        
        model.clear()
        mover.value = 0
        mover.maximumValue = 0
        sliceTime.text = ""
        sliceMaxValue.text = ""
        sliceAverage.text = ""
        numberSliceMaxValue.text = ""
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
            MouseArea{
                id: delegateMouse
                anchors.fill: parent
                hoverEnabled: true
            }
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

    Rectangle{
        id: infoBackground
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height * 0.33
        border.color: "#090"
        color: "#fff"
        opacity: 0.5
        border.width: 2
        radius: 10
        width: Math.max(parent.width * 0.12, numberSliceMaxValue.width + 10)
        height: info.height + 20
        visible: model.count
    }

    Column{
        id: info
        x: infoBackground.x + 4
        anchors.verticalCenter: infoBackground.verticalCenter
        Text{
            id: sliceTime
            objectName: "sliceTime"
            color: "#2c6d0c"
            font.pointSize: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text{
            id: numberSliceMaxValue
            objectName: "numberSliceMaxValue"
            color: "#2c6d0c"
            font.pointSize: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text{
            id: sliceMaxValue
            objectName: "sliceMaxValue"
            color: "#2c6d0c"
            font.pointSize: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
        Text{
            id: sliceAverage
            objectName: "sliceAverage"
            color: "#2c6d0c"
            font.pointSize: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    Slider{
        id: mover
        objectName: "mover"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -5
        opacity: hovered ? 1: 0.5
        minimumValue: 0
        maximumValue: 0
        stepSize: 1
        height: 28
        updateValueWhileDragging: true
    }

    Slider{
        id: maxValueRanger
        opacity: hovered ? 1 : 0.2
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        minimumValue: 0
        maximumValue: 100
        value: 3
        stepSize: 1
        width: 30
        height: parent.height * 0.2
        orientation: Qt.Vertical
        updateValueWhileDragging: true
    }
}
