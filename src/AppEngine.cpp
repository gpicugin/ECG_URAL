#include "AppEngine.h"
#include "QtMath"
AppEngine::AppEngine(QObject *parent)
    : QObject{parent}
{
    channels.resize(ECG_channels::size);

    InitialParamsOfChart params;
    params.ppi = QGuiApplication::primaryScreen()->physicalDotsPerInch();
    params.sampleRate_hz = 150;
    params.minSweep_mm_per_s = 25;

    for(auto& channel : channels)
    {
        channel.chart = new SweepChart(this, &params);
    }

    COMEmulationTimer = new QTimer;

    COMEmulationTimer->setInterval(1000);

    connect(COMEmulationTimer, QTimer::timeout, this, AppEngine::pushData);

    COMEmulationTimer->start();
}

AppEngine::~AppEngine()
{
    for(auto& channel : channels)
    {
        delete channel.chart;
    }

    delete COMEmulationTimer;
}

SweepChart* AppEngine::getSweepChart(int index)
{
    if(index < channels.size())
        return channels[index].chart;
}

AppEngine::pushData()
{
    for(auto& channel : channels)
    {
        for(int i = 0; i < 150; i++)
            channel.buffer.enqueue( qSin(2*3.14*i/150.)+1);

        channel.chart->pushData(&channel.buffer);
    }
}
