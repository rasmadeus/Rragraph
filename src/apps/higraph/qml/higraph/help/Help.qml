import QtQuick 2.0

Rectangle {
    HelpBackground{
        anchors.fill: parent
    }
    Text{
        color: "#693e0c"
        elide: Text.ElideMiddle
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        text: qsTr("
            <h3>О программе</h3>
            Higraph v1.0.0 является очень нежной программой, поэтому кормить её нужно<br>
            исключительно текстовыми файлами, которые сформированны по заветам очень грозного<br>
            графопостроителя Rragraph. Причём первый столбец она не будет переваривать ни в <br>
            жаренном ни в паренном виде, так как таким избалованным особам вреден учёт времени.<br>
            Если вы сидите перед монитором без галстука или бабочки, программа может обидеться и<br>
            отказаться работать. Также Higraph может получить душевное расстройство,<br>
            если вашу видеокарточку обхаживают  драйвера бальзаковского возраста,<br>
            а маленькие мониторы вызывают у неё такие приступы смеха, что она<br>
            сворачивается в калачик от острых колик в животе. Так что не перекармливайте Higraph,<br>
            но организуйте для неё просторный вольер и будет <br>
            счастье для всех даром и ни кто не уйдёт обиженным.
            <h3>Заказчик, тестер</h3>
            Кожнев А.Н.
            <h3>Разработчик</h3>
            rasmadeus@gmail.com
            <h3>Лицензия</h3>
            General Public License v.1.0,<br>
            программа создана на базе ОАО МКБ \"Факел\" 80 отдел 9 бригада<br>
            г. Химки, декабрь 2013 года
        ")
        smooth: true
        font.pointSize: 14
        styleColor: "#550"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }
}
