#include "serialportecg.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>
#include <QTime>

SerialPortECG::SerialPortECG(QObject *parent)
    : QObject(parent)
{

}

SerialPortECG::~SerialPortECG()
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

void SerialPortECG::connectSerialPort()
{
    QString namePort;

    namePort = QString("COM%1").arg(NumSerialPort::ECG);

    //    foreach (const QSerialPortInfo &info,
    //             QSerialPortInfo::availablePorts())
    //    {
    //        QSerialPort port;
    //        port.setPort(info);

    //        //заглушка, что бы не повисала на первом коме
    //        if (port.portName() == QString("COM1"))
    //        {

    //            continue;
    //        }

    //        if(port.open(QIODevice::ReadWrite))
    //        {
    //            namePort = port.portName();

    //            break;
    //        }
    //    }

    //    if (namePort.isEmpty())
    //    {

    //        return;
    //    }

    serial = new QSerialPort();
    serial->setPortName(namePort);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);
    serial->clear();

    connect(serial,
            &QSerialPort::readyRead,
            this,
            &SerialPortECG::readData);

    if (serial->isOpen())
    {

    }
    else
    {

        delete serial;
        serial = nullptr;
    }
}

void SerialPortECG::readData()
{
    while (serial->bytesAvailable() >= SIZE_PACKAGE_ECG_ALTONICA)
    {
        QByteArray byteArrayData = serial->read(SIZE_PACKAGE_ECG_ALTONICA);

        QVector <uint8_t> vectorData;
        vectorData.resize(SIZE_PACKAGE_ECG_ALTONICA);

        for(int i = 0; i < byteArrayData.size(); i++)
        {
            vectorData[i] = static_cast<uint8_t>(byteArrayData.at(i));
        }



        emit packageFormChange(vectorData);
    }
}

void SerialPortECG::writeData(QByteArray byteArrayData)
{


    if (serial == nullptr)
    {
        return;
    }

    serial->write(byteArrayData);
}
