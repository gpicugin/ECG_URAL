#include "AppEngine.h"
#include "QtMath"
AppEngine::AppEngine(QObject *parent)
    : QObject{parent}
{
    channels.resize(1);

    InitialParamsOfChart params;
    params.ppi_x = QGuiApplication::primaryScreen()->logicalDotsPerInchX();
    params.ppi_y = QGuiApplication::primaryScreen()->logicalDotsPerInchY();

    params.sampleRate_hz = 150;
    params.minSweep_mm_per_s = 25;

    for(auto& channel : channels)
    {
        channel.chart = new SweepChart(this, &params);
    }

    COMEmulationTimer = new QTimer;
    COMTimer = new QTimer;
    screenTimer = new QTimer;

    port = new SerialPort;


    COMEmulationTimer->setInterval(40);
    COMTimer->setInterval(40);
    screenTimer->setInterval(40);

    connect(COMTimer, QTimer::timeout, port, SerialPort::readData);
    connect(screenTimer, QTimer::timeout, this, AppEngine::updateScreen);
    connect(port, SerialPort::packageChanged, this, AppEngine::pushData);

    port->connectSerialPort();


    COMEmulationTimer->start();
    COMTimer->start();
    screenTimer->start();
}

AppEngine::~AppEngine()
{
    for(auto& channel : channels)
    {
        delete channel.chart;
    }

    delete COMEmulationTimer;
    delete COMTimer;
    delete screenTimer;
    delete port;
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

void AppEngine::pushData(QVector<int> package)
{
    // //for(auto& channel : channels)
    // {
    //     for(int i = 0; i < 6; i++,j++)
    //     {
    //         channels[0].buffer.enqueue( qSin(2*3.14*j/150.) + 6);
    //     }
    // }
    qDebug() << package.size();
    for(auto number : package)
    {
        channels[0].buffer.enqueue(number);
    }
}
