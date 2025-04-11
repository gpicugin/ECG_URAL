#include "SweepChart.h"
#include <QtMath>

SweepChart::SweepChart(QObject *parent, InitialParamsOfChart* params)
    :   m_minSweep_mmPerSec(params->minSweep_mm_per_s),
        m_xAxisInterval(1 / params->sampleRate_hz),
        m_ppi_x(params->ppi_x),
        m_ppi_y(params->ppi_y)
{
    // qDebug() << m_xAxisInterval;
    m_pPoints = new QVector<QPointF>;    
}

SweepChart::~SweepChart()
{
    delete m_pPoints;
}

void SweepChart::setOrigin(QPointF point)
{
    m_origin = point;

    m_xUpperLimit = m_origin.x();

    m_xLowerLimit = m_origin.x();
}

double SweepChart::getXUpperLimit() const
{
    return m_xUpperLimit;
}

double SweepChart::getXLowerLimit() const
{
    return m_xLowerLimit;
}

double SweepChart::getYLowerLimit() const
{
    return m_yLowerLimit;
}

int SweepChart::getNumDisplayPoints() const
{
    return m_numDisplayPoints;
}

int SweepChart::getSize() const
{
    return m_size;
}

double SweepChart::getXAxisInterval() const
{
    return m_xAxisInterval;
}

void SweepChart:: xShiftTo(double xCoord)
{
    if(xCoord > m_xUpperLimit || xCoord < m_xLowerLimit)
        return;

    int index = qRound((xCoord - m_xLowerLimit) / m_xAxisInterval);

    m_currentIndex = index;
}

void SweepChart::xShiftBy(int shift)
{
    if(shift > m_numDisplayPoints)
        shift = shift % m_numDisplayPoints;

    if(shift < -m_numDisplayPoints)
        shift = -(qAbs(shift) % m_numDisplayPoints);

    m_currentIndex += shift;

    if(m_currentIndex > m_numDisplayPoints)
    {
        m_currentIndex %= m_numDisplayPoints;
    }

    if(m_currentIndex < 0)
    {
        m_currentIndex = m_numDisplayPoints - m_currentIndex;
    }

    emit chartDataChanged();
}

void SweepChart::recalculateX()
{
    m_xLowerLimit = m_origin.x();

    // qDebug() << m_width_n_pixels << m_ppi_x << m_sweepRate_mmPerSec << m_xLowerLimit;

    // double sweepRate_dPerSec = m_sweepRate_mmPerSec / 25.4;

    m_xUpperLimit = (m_width_n_pixels / m_ppi_x * 25.4 / m_sweepRate_mmPerSec)+ m_xLowerLimit;

    //m_xUpperLimit /= 25;

    m_numDisplayPoints = qCeil((m_xUpperLimit - m_xLowerLimit) / m_xAxisInterval);
}

void SweepChart::recalculateY()
{
    m_yLowerLimit = m_origin.y();

    qDebug() << "y" << m_yLowerLimit;

    m_yUpperLimit = (m_height_n_pixels) / m_ppi_y * 25.4 / m_sensitivity_mmPermV + m_yLowerLimit;
}

void SweepChart::startUpdateChart()
{
    m_isEnable = true;
}

void SweepChart::stopUpdateChart()
{
    m_isEnable = false;
}

void SweepChart::enableChannel(bool enable)
{
    m_isEnable = enable;
}

double SweepChart::onXAxisWidthChanged(int pixels)
{
    m_width_n_pixels = pixels;

    recalculateX();

    m_pPoints->clear();

    // if(m_pPoints->size() < m_numDisplayPoints);
    // {
    //     QQueue<double> data;
    //     for(int i = 0; i < m_numDisplayPoints - m_pPoints->size(); i++)
    //         data.enqueue(m_origin.y());
    //     pushData(&data);
    // }

    emit chartDataChanged();

    return m_xUpperLimit;
}

double SweepChart::onYAxisWidthChanged(int pixels)
{
    m_height_n_pixels = pixels;

    recalculateY();

    m_pPoints->clear();

    emit chartDataChanged();

    return m_yUpperLimit;
}

void SweepChart::onSweepRateChanged(double mm_per_s)
{
    m_sweepRate_mmPerSec = mm_per_s;

    recalculateX();

    m_currentIndex = 0;   

    if(m_pPoints->size() < m_numDisplayPoints)
    {
        QPointF point = m_pPoints->last();
        while(m_pPoints->size() < m_numDisplayPoints)
            m_pPoints->append(point);
    }

    emit chartDataChanged();
}

void SweepChart::pushData(QQueue<double> *data)
{
    if(m_numDisplayPoints == 1)
    {
        QPointF point = QPointF(m_origin.x(), data->last());

        setOrigin(point);
        (*m_pPoints).append(point);

        for(int i = 0; i < data->size(); i++)
            emit rollOver();

        emit chartDataChanged();

        return;
    }

    while(!data->isEmpty())
    {
        if(m_currentIndex == 0 && m_pPoints->size() != 0)
        {
            emit rollOver();
        }

        if(m_pPoints->size() <= m_currentIndex)
            m_pPoints->append(QPointF(m_xLowerLimit + m_xAxisInterval * (m_currentIndex), data->dequeue()));
        else
            (*m_pPoints)[m_currentIndex] = QPointF(m_xLowerLimit + m_xAxisInterval * (m_currentIndex), data->dequeue());

        m_currentIndex++;

        if(m_currentIndex == m_numDisplayPoints)
        {
            m_currentIndex = 0;
            // qDebug() << "m_currentIndex rollOver";
        }
    }
    emit chartDataChanged();
}

int SweepChart::getLine(QtCharts::QLineSeries *lineSeries1, QtCharts::QLineSeries *lineSeries2)
{
    if(lineSeries1 == nullptr || lineSeries2 == nullptr) {
        qDebug() << "return 0";
        return 0;
    }

    // критерий
    if(m_numDisplayPoints != 1)
    {
        if(m_currentIndex == 0)
        {
            lineSeries1->replace(m_pPoints->mid(0, m_numDisplayPoints)); // граничные случаи
            lineSeries2->clear();
        }
        else
        {
            lineSeries1->replace(m_pPoints->mid(0, m_currentIndex)); // граничные случаи
            lineSeries2->replace(m_pPoints->mid(m_currentIndex, m_numDisplayPoints - m_currentIndex));
        }
    }
    else
    {
        lineSeries1->clear();
        lineSeries1->append(m_origin);
        lineSeries2->clear();
    }

    return m_currentIndex;
}
