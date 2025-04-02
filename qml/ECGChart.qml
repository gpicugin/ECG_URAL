import QtQuick 2.15
import QtQuick.Controls 2.0
import QtCharts 2.15
import QtQuick.Layouts 1.15
import StyleSettings 1.0

ChartView {

    margins { right: 0; bottom: 0; left: 0; top: 0 }

    legend.visible: false

    backgroundRoundness: 0

    backgroundColor: Style.colorBackGraphECG

    ValueAxis
    {
        id: _axisX

        min: 0

        tickType: ValueAxis.TicksDynamic
        tickAnchor: 0

        max: 11.45
        tickInterval: 4
        minorTickCount: 3

        labelFormat: "%d c"
        labelsFont.pixelSize: Style.fontSizeLabelGraph

        labelsColor:        Style.colorTextLabelGraphECG_X
        gridLineColor:      Style.colorGridLaynerECG
        minorGridLineColor: Style.colorGridLaynerECG
        titleBrush:         Style.colorTextLabelGraphECG_X
    }

    ValueAxis
    {
        id: _axisY

        min: 0

        tickType: ValueAxis.TicksDynamic
        tickAnchor: 0

        //критичный параметр
        max: 3.9
        minorTickCount: 4
        tickInterval: 5

        //нужно для выравнивания графиков
        labelFormat: "%d0"

        labelsFont.pixelSize: Style.fontSizeLabelGraph

        labelsColor:        Style.colorTextLabelGraphECG_Y
        gridLineColor:      Style.colorGridLaynerECG
        minorGridLineColor: Style.colorGridLaynerECG
        titleBrush:         Style.colorTextLabelGraphCO2
    }

    LineSeries {
        id: _LineSeries1
        axisX: _axisX
        axisY: _axisY
        color: "#00FF00"
    }

    LineSeries {
        id: _LineSeries2
        axisX: _axisX
        axisY: _axisY
        color: "#00FF00"
    }

    AreaSeries {
        id: _cursor
        axisX: _axisX
        axisY: _axisY
        borderColor: Style.colorBackGraphECG
        borderWidth: _axisX.max * 0.5
        color: Style.colorBackGraphECG

        upperSeries: LineSeries {
            id: _cursorLine
            color: Style.colorBackGraphECG
        }
    }

    // Component.onCompleted: {
    //     _axisX.max = GraphSPO2.onXAxisWidthChanged(_graphSPO2.plotArea.width)
    // }

    Connections
    {
        target: GraphSPO2

        function onChartDataChanged()
        {
            var index = GraphSPO2.getLine(_LineSeries1, _LineSeries2)

            _cursorLine.clear()

            var space = _axisX.max / 50

            if(index < _LineSeries1.count - space)
            {
                var point = _LineSeries1.at(index - 1)
                _cursorLine.append(point.x, _axisY.max)

                _cursorLine.append(point.x + (space), _axisY.max)
            }
        }

        function onSetHSweepSPO2Changed(displayRange)
        {
            _axisX.max = displayRange
        }

        function onClearChart()
        {
            console.log("clear")
            _LineSeries1.clear();
            _LineSeries2.clear();
        }
    }
}
