#include "SerialPort.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QFile>
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
    QString txt;

    QFile inFile("COM.txt");
    inFile.open(QIODevice::ReadOnly | QIODevice::Append);
    QTextStream ts(&inFile);

    if(ts.readAll().size() == 0)
    {
        const auto serialPortInfos = QSerialPortInfo::availablePorts();

        if(serialPortInfos.size() != 0)
            namePort = serialPortInfos.last().portName();
        else
        {
            qDebug() << "NO_PORT";
        }
    }
    else
    {
        namePort = ts.readAll();
    }

    serial = new QSerialPort();
    serial->setPortName(namePort);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    connect(serial, &QSerialPort::readyRead, this,  &SerialPort::readData);
    connect(serial, &QSerialPort::errorOccurred, this, &SerialPort::handleError);


    if (serial->open(QSerialPort::ReadWrite))
    {
        qDebug() << "open";
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
    QVector<double> result;
    while (serial->bytesAvailable() > 10)
    {
        QString data = serial->readLine();

        // qDebug() << data.toInt();

        result.append(data.toDouble() / (350.0 / 2.3));
    }

    // qDebug() << result;

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
