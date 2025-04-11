import QtQuick 2.15
import QtQuick.Window 2.15
import StyleSettings 1.0

Window {
    id: _mainWindow
    width: Screen.width / 2
    height: Screen.height / 2
    visible: true
    title: qsTr("Hello World")


    ECGFrame {
        color: Style.colorBackGraphECG
        anchors.fill: parent
    }
}
