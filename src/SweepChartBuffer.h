#ifndef SWEEPCHARTBUFFER_H
#define SWEEPCHARTBUFFER_H
#include <QPointF>
#include <QDebug>
#include <QQueue>

int mod_non_negative(int value, int base);

class SweepChartBuffer
{
public:
    SweepChartBuffer(int size = 1, double defaultValue = 0);
    ~SweepChartBuffer() = default;

    bool pushData(double y);
    int  getNumDisplayPoints() const;
    int  getSize() const;
    int  getStartPos() const;
    int  getCurrentPos() const;
    int  getEndPos() const;
    void setNumDisplayPoints(int size);
    bool shiftBuffer(int shift);
    QVector<double> getNew() const;
    QVector<double> getOld() const;

private:
    QVector<double> getArr(int index, int size) const;
    QVector<double> m_Points;
    int     m_numDisplayPoints = 0;
    int     m_startPos         = 0;
    int     m_numNewPoints     = 0;
    double  m_defaultValue     = 1.5;
};

#endif // SWEEPCHARTBUFFER_H
