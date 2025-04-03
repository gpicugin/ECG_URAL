#include "AppEngine.h"

AppEngine::AppEngine(QObject *parent)
    : QObject{parent}
{
    channels.resize(ECG_channels::size);

    InitialParamsOfChart params;
    params.ppi = QGuiApplication::primaryScreen()->physicalDotsPerInch();
    params.sampleRate_hz = 500;
    params.minSweep_mm_per_s = 25;

    for(auto& channel : channels)
    {
        channel.chart = new SweepChart(this, &params);
        channel.buffer = new QQueue<double>;
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
        delete channel.buffer;
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
            channel.buffer->enqueue(i % 5);

        channel.chart->pushData(channel.buffer);
    }
}
