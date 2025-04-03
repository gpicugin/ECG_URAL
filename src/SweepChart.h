#ifndef SWEEPCHART_H
#define SWEEPCHART_H

#include <QObject>
#include <QQueue>
#include <QPointF>
#include <QtCharts/QLineSeries>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>

inline int pointsPerChart(int chartWidth_mm, double sampleRate_Hz, double sweepRate_mm_sec)
{
    return (int)(chartWidth_mm * sampleRate_Hz / sweepRate_mm_sec);
}
inline double timeAxisRange_s(int n_points, double sampleRate)
{
    return n_points / sampleRate;
}

struct InitialParamsOfChart
{
    qreal ppi = QGuiApplication::primaryScreen()->physicalDotsPerInch();
    double sampleRate_hz = 1;
    double minSweep_mm_per_s = 1;
};

class SweepChart : public QObject
{
    Q_OBJECT
public:
    explicit SweepChart(QObject *parent = nullptr, InitialParamsOfChart* params = nullptr);
    ~SweepChart();
    void    setOrigin(QPointF point);
    double  getXUpperLimit() const;
    double  getXLowerLimit() const;
    double  getYUpperLimit() const;
    double  getYLowerLimit() const;
    int     getNumDisplayPoints() const;
    int     getSize()             const;
    double  getXAxisInterval()    const;
    void    xShiftTo(double xCoord);
    void    xShiftBy(int shift);

protected:
    void updateSweepRate();
    void resizeGraphData(double minDisplayRange);

protected:
    QVector<QPointF>* m_pPoints            = nullptr;
    int               m_size               = 1; // количество точек при мин разверстке
    double            m_ppi                = 0;
    double            m_sweepRate_mmPerSec = 25;
    double            m_sensitivity_mmPermV= 20;

    double            m_minSweep_mmPerSec  = 0;
    double            m_sampleRate_hz      = 0;
    double            m_width_n_pixels     = 0;
    double            m_height_n_pixels    = 0;
    double            m_displayRange       = 0;
    double            m_PixelSize          = 0;
    bool              m_isEnable           = true;
    int               m_numDisplayPoints   = 1; // количество точек при текущей разверстке
    double            m_timeOfOnePoint;

private:
    QPointF m_origin        = QPointF(0,0);
    double  m_xAxisInterval = 1.0;
    double  m_xUpperLimit   = 0.0;
    double  m_xLowerLimit   = 0.0;
    double  m_yUpperLimit   = 0.0;
    double  m_yLowerLimit   = 0.0;
    int     m_currentIndex  = 0;
    int     m_startIndex    = 0;

private:
    void recalculateX();
    void recalculateY();

public slots:
    void pushData(QQueue<double> *data);
    void startUpdateChart();
    void stopUpdateChart();
    void enableChannel(bool enable);
    int  getLine(QtCharts::QLineSeries *lineSeries1, QtCharts::QLineSeries *lineSeries2);
    double onXAxisWidthChanged(int pixels);
    double onYAxisWidthChanged(int pixels);

    void onSweepRateChanged(double mm_per_s);

signals:
    void clearChart();
    void chartDataChanged();
    void onRollOver();
};

#endif // SWEEPCHART_H
