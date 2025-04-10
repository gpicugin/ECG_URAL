#ifndef SERIALPORTECG_H
#define SERIALPORTECG_H

#include <QObject>

class QSerialPort;

class SerialPortECG
{
    Q_OBJECT
public:
    explicit SerialPortECG(QObject *parent = nullptr);
    ~SerialPortECG();

public slots:
    void connectSerialPort();

    void readData();
    void writeData(QByteArray byteArrayData);

private:
    QSerialPort *serial = nullptr;

signals:
    void packageFormChange(const QVector <uint8_t> &vectorData);
};

#endif // SERIALPORTECG_H
