#include "AppEngine.h"
#include "QtMath"
AppEngine::AppEngine(QObject *parent)
    : QObject{parent}
{
    channels.resize(1);

    InitialParamsOfChart params;
    params.ppi = QGuiApplication::primaryScreen()->physicalDotsPerInch();
    params.sampleRate_hz = 150;
    params.minSweep_mm_per_s = 25;

    for(auto& channel : channels)
    {
        channel.chart = new SweepChart(this, &params);
    }

    COMEmulationTimer = new QTimer;

    screenTimer = new QTimer;


    COMEmulationTimer->setInterval(40);

    screenTimer->setInterval(40);

    connect(COMEmulationTimer, QTimer::timeout, this, AppEngine::pushData);
    connect(screenTimer, QTimer::timeout, this, AppEngine::updateScreen);


    COMEmulationTimer->start();
    screenTimer->start();
}

AppEngine::~AppEngine()
{
    for(auto& channel : channels)
    {
        delete channel.chart;
    }

    delete COMEmulationTimer;
    delete screenTimer;
}

SweepChart* AppEngine::getSweepChart(int index)
{
    if(index < channels.size())
        return channels[index].chart;
}

void AppEngine::updateScreen()
{
    for(auto& channel : channels) {
        if(!channel.buffer.isEmpty())
            channel.chart->pushData(&channel.buffer);
    }
}

static int j = 0;

AppEngine::pushData()
{
    //for(auto& channel : channels)
    {
        for(int i = 0; i < 6; i++,j++)
        {
            channels[0].buffer.enqueue( qSin(2*3.14*j/150.) + 1.);
        }
    }
}
