#ifndef SERIALPORT_H
#define SERIALPORT_H
#include <QSerialPort>
#include <QObject>

class QSerialPort;

class SerialPort : public QObject
{
    Q_OBJECT

public:
    SerialPort(QObject *parent = nullptr);
    ~SerialPort();

public slots:
    void connectSerialPort();

    void readData();
    void writeData(QByteArray byteArrayData);
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *serial = nullptr;

signals:
    void packageChanged(QVector<int>);
};

#endif // SERIALPORT_H
