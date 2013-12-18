import QtQuick 2.0

Rectangle {
    HelpBackground{
        anchors.fill: parent
    }
    Text{
        color: "#e2800f"
        elide: Text.ElideMiddle
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        text: qsTr("
            Данная программа предназначена для просмотра<br>
            набора параметров ввиде гистрограмм.<br>
            Разработчики программы осознают, что для них<br>
            уже давно в аду приготовлен специальный котёл,<br>
            но тем не менее инструкция для пользователя<br>
            будет ограничена этой страничкой.<br>
            Спасибо за внимание, счастья для всех даром<br>
            и пусть никто не уйдёт обиженным © БС
        ")
        smooth: true
        font.pointSize: 14
        styleColor: "#550"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
