#include "serialport.h"
#include "SerialPortGlobal.h"

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

    namePort = QString("COM%1").arg(NumSerialPort::COMMON);

    serial = new QSerialPort();
    serial->setPortName(namePort);
    serial->setBaudRate(QSerialPort::Baud38400);
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


    while (serial->bytesAvailable() >= SIZE_PACKAGE_COMMON)
    {
        QByteArray byteArrayData = serial->read(1);
        uint8_t firstByte = static_cast<uint8_t>(byteArrayData.at(0));

        //  if ((firstByte & 0x80) != 0x80)continue;

        byteArrayData = serial->read(1);
        uint8_t secondByte = static_cast<uint8_t>(byteArrayData.at(0));




        emit packageFormChange((firstByte << 8) | secondByte);
    }

    //    while (serial->bytesAvailable())
    //    {
    //        QByteArray byteArrayData = serial->read(1);
    //        uint8_t firstByte = static_cast<uint8_t>(byteArrayData.at(0));


    //    }
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
