#include "SerialPort.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>

SerialPort::SerialPort(QObject *parent)
    : QObject(parent)
{
}

SerialPort::~SerialPort()
{
    if (serial != nullptr)
    {
        if (serial->isOpen())
        {
            serial->close();
        }
        delete serial;
    }
}

void SerialPort::connectSerialPort()
{
    QString namePort;

    namePort = QString("COM%1").arg(5);

    serial = new QSerialPort();
    serial->setPortName(namePort);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    // serial->setReadBufferSize(1024 * 1024);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    //serial->open(QIODevice::ReadWrite);

    connect(serial, &QSerialPort::readyRead, this,  &SerialPort::readData);
    connect(serial, &QSerialPort::errorOccurred, this, &SerialPort::handleError);


    if (serial->open(QSerialPort::ReadWrite))
    {
        serial->clear();
    }
    else
    {

        delete serial;
        serial = nullptr;
    }
}

void SerialPort::readData()
{
    QVector<int> result;
    while (serial->bytesAvailable() > 10)
    {
        QString data = serial->readLine();

        // qDebug() << data;

        // qDebug() << data.toInt();

        result.append(data.toInt());
    }

    emit packageChanged(result);
}

void SerialPort::writeData(QByteArray byteArrayData)
{
    if (serial == nullptr)
    {
        return;
    }

    serial->write(byteArrayData);
}

void SerialPort::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ReadError) {

        serial->close();
    }
}
