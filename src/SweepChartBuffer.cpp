#include "SweepChartBuffer.h"

SweepChartBuffer::SweepChartBuffer(int size, double defaultValue) :
    m_Points(size, defaultValue),
    m_defaultValue(defaultValue)
{    
    m_numDisplayPoints = size;
    m_numNewPoints = 0;
}

int SweepChartBuffer::getNumDisplayPoints() const
{
    return m_numDisplayPoints;
}

int SweepChartBuffer::getSize() const
{
    return m_Points.size();
}

int SweepChartBuffer::getStartPos() const
{
    return m_startPos;
}

int SweepChartBuffer::getCurrentPos() const
{
    int currPos = m_startPos;
    currPos = mod_non_negative(currPos + m_numNewPoints - 1, m_Points.size());
    return currPos;
}

int SweepChartBuffer::getEndPos() const
{
    int endPos = m_startPos;
    endPos = mod_non_negative(endPos + m_numNewPoints - m_numDisplayPoints, m_Points.size());
    return endPos;
}

void SweepChartBuffer::setNumDisplayPoints(int size)
{
    int oldNDP =  m_numDisplayPoints;
    m_numDisplayPoints = size;

    if(m_Points.size() < m_numDisplayPoints)
    {
        int index = getCurrentPos();
        index = mod_non_negative(index + 1,m_Points.size());
        for(int i = oldNDP; i < size; i++)
        {
            m_Points.insert(index, m_defaultValue);
            index++;
        }
    }
    m_startPos = getCurrentPos();
    m_startPos = mod_non_negative(m_startPos + 1,m_Points.size());
    m_numNewPoints = 0;
}

bool SweepChartBuffer::shiftBuffer(int shift)
{
    int currPos = getCurrentPos();
    m_numNewPoints = mod_non_negative( shift + m_numNewPoints, m_numDisplayPoints);
    m_startPos = mod_non_negative(currPos - m_numNewPoints + 1, m_Points.size());

    return !m_numNewPoints;
}

QVector<double> SweepChartBuffer::getNew() const
{    
    return getArr(m_startPos, m_numNewPoints);
}

QVector<double> SweepChartBuffer::getOld() const
{
    return getArr(getEndPos(), m_numDisplayPoints - m_numNewPoints);
}

QVector<double> SweepChartBuffer::getArr(int index, int size) const
{
    QVector<double> tmp;

    for (int i = 0; i < size; i++)
    {
        tmp.append(m_Points[index]);
        index = mod_non_negative(index + 1,m_Points.size());
    }

    return tmp;
}

bool SweepChartBuffer::pushData(double y)
{
    int index = getCurrentPos();
    index = mod_non_negative(index + 1, m_Points.size());

    m_Points[index] = y;

    if(++m_numNewPoints > m_numDisplayPoints - 1)
    {
        m_startPos = mod_non_negative(index + 1, m_Points.size());

        m_numNewPoints = 0;
        return true;
    }
    else
        return false;
}

int mod_non_negative(int value, int base)
{
    while(value >= base)
    {
        value -= base;
    }
    while(value < 0)
    {
        value += base;
    }
    return value;
}
