import QtQuick 2.15
import QtQuick.Controls 2.0
import QtCharts 2.15
import QtQuick.Layouts 1.15


Rectangle {
    id: _ECGFrame

    RowLayout
    {
        anchors.fill: parent
        Repeater
        {
            model : 2
            ColumnLayout
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                spacing: 0
                Repeater {
                    model: 3
                    delegate: ECGChart {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}
