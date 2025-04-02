#include "AppEngine.h"

AppEngine::AppEngine(QObject *parent)
    : QObject{parent}
{
    channels.resize(ECG_channels::size);

    InitialParamsOfChart params;

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

AppEngine::pushData()
{
    for(auto& channel : channels)
    {
        for(int i = 0; i < 150; i++)
            channel.buffer->enqueue(i % 5);

        channel.chart->pushData(channel.buffer);
    }
}
