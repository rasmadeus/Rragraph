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
        var res = maxValueRanger.value === 0 ? 10 : getRearrangedValue(value) / maxValueRanger.value * view.height
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
            isRevert: true
            y: view.height - height
            mainColor: Qt.rgba(Math.random(255), Math.random(255), Math.random(255));
            secondColor: histogram.mainColor
            id: delegateBody
            width: getDelegateWidth()
            height: getDelegateHeight(value)
        }
    }

    signal moverPosWasChanged()
    Row{
        id: histograMenu
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        Slider{
            id: mover
            objectName: "mover"
            minimumValue: 0
            maximumValue: 0
            stepSize: 1
            width: 200
            updateValueWhileDragging: true
            onValueChanged: moverPosWasChanged()
        }
        Slider{
            id: maxValueRanger
            objectName: "maxValueRanger"
            minimumValue: 0
            maximumValue: 100
            value: 3
            stepSize: 1
            width: 200
            anchors.top: parent.top
            updateValueWhileDragging: true
        }
    }
    ListView{
        id: view
        anchors.top: histograMenu.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 10
        keyNavigationWraps: true
        model: model
        delegate: delegate
        orientation: ListView.Horizontal
    }
}
