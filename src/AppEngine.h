#ifndef APPENGINE_H
#define APPENGINE_H
#include "SweepChart.h"
#include "SweepChartBuffer.h"
#include "serialport.h"
#include <QTimer>
#include <QObject>

struct Sweep {
    SweepChart* chart;
    QQueue<double> buffer;
};

enum ECG_channels {
    I,
    II,
    III,
    AVR,
    AVL,
    AVF,
    size = 7
};

class AppEngine : public QObject
{
    Q_OBJECT
public:
    explicit AppEngine(QObject *parent = nullptr);
    ~AppEngine();

public slots:
    SweepChart *getSweepChart(int index);
    void updateScreen();

private:
    QVector<Sweep> channels;

    QTimer* COMEmulationTimer;
    QTimer* COMTimer;
    QTimer* screenTimer;
    SerialPort* port;

private slots:
    void pushData(QVector<double> package);

signals:
};

#endif // APPENGINE_H
