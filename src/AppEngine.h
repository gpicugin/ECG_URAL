#ifndef APPENGINE_H
#define APPENGINE_H
#include "SweepChart.h"
#include "SweepChartBuffer.h"
#include "serialport.h"
#include <QTimer>
#include <QObject>
/*
задача считать данные с ацп, сконфигурировать ком-порт из двух знач ацп выводят 6 клинич отведений
делают фильтр полостно-заграждающий до 60 гц, масштабируют и по компорту отправляют
-Это была задача АЦП
150 раз в секунду 6 значений - задача проэнтерпретировать и распарсить протокол
задача: распарсить протокол и составить в векторы
работаю с ком-портом и парсю протокол
- сделать бля за неделю
*/
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
    void pushData(QVector<int> package);

signals:
};

#endif // APPENGINE_H
