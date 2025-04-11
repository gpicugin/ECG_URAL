import QtQuick 2.15
import QtQuick.Controls 2.0
import QtCharts 2.15
import QtQuick.Layouts 1.15
import StyleSettings 1.0
import SweepChart 1.0

ChartView {
    id: _view

    property int sweepIndex

    property SweepChart engine

    margins { right: 0; bottom: 0; left: 0; top: 0 }

    legend.visible: false

    backgroundRoundness: 0

    backgroundColor: Style.colorBackGraphECG

    ValueAxis
    {
        id: _axisX

        min: 0
        max: 2

        tickType: ValueAxis.TicksDynamic
        tickAnchor: 0

        minorTickCount: 3
        tickInterval: 4

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

        tickType: ValueAxis.TicksDynamic
        tickAnchor: 0

        //критичный параметр
        minorTickCount: 0
        tickInterval: 5

        //нужно для выравнивания графиков
        labelFormat: "%d"

        labelsFont.pixelSize: Style.fontSizeLabelGraph

        labelsColor:        Style.colorTextLabelGraphECG_X
        gridLineColor:      Style.colorGridLaynerECG
        minorGridLineColor: Style.colorGridLaynerECG
        titleBrush:         Style.colorTextLabelGraphECG_X
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
    Component.onCompleted : {
        engine = appEngine.getSweepChart(parent.sweepIndex)
        _axisY.max = engine.onYAxisWidthChanged(_view.plotArea.height)
        _axisY.min = engine.getYLowerLimit()
        print(_axisY.min)
        _axisX.max = engine.onXAxisWidthChanged(_view.plotArea.width)
    }

    onWidthChanged: {
        _axisX.max = engine.onXAxisWidthChanged(_view.plotArea.width)
    }

    onHeightChanged: {
        _axisY.max = engine.onYAxisWidthChanged(_view.plotArea.height)

    }

    Connections
    {
        target: engine

        function onChartDataChanged()
        {
            var index = engine.getLine(_LineSeries1, _LineSeries2)
            var space = 25

            if(_LineSeries1.count >= space)
                _LineSeries1.removePoints(_LineSeries1.count - space, space)

            if(_LineSeries2.count >= space)
                _LineSeries2.removePoints(0, space)
        }

        function onClearChart()
        {
            console.log("clear")
            _LineSeries1.clear();
            _LineSeries2.clear();
        }
    }
}
