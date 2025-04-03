import QtQuick 2.15
import QtQuick.Controls 2.0
import QtCharts 2.15
import QtQuick.Layouts 1.15


Rectangle {
    id: _ECGFrame

    GridLayout {
        id: _grid
        columns: 1
        anchors.fill: parent
        Repeater
        {
            id: _rep
            property int count: 1
            model: count
            delegate: ECGChart
            {
                width: _mainWindow.width / _grid.columns
                height: _mainWindow.height / (_rep.count / _grid.columns)
                sweepIndex: index
            }
        }
    }
}
