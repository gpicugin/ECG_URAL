import QtQuick 2.15
import QtQuick.Controls 2.0
import QtCharts 2.15
import QtQuick.Layouts 1.15


Rectangle {
    id: _ECGFrame

    GridLayout {
        id: _grid
        columns: 2
        anchors.fill: parent
        Repeater
        {
            model: 6
            delegate: ECGChart
            {
                width: _mainWindow.width / 2
                height: _mainWindow.height / 3
                sweepIndex: index
            }
        }
    }
    Component.onCompleted : {
        print(width)
        print(height)
    }
}
