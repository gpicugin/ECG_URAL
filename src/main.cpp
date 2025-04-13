#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include "AppEngine.h"
#include "SweepChart.h"

void myMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & msg)
{
    QString txt;
    switch (type)
    {
    case QtDebugMsg:
        txt = QString("%1").arg(msg);
        break;
    case QtWarningMsg:
        //txt = QString("Warning: %1").arg(msg);
        return;
        break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
        break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
        // abort();
    case QtInfoMsg:
        break;
    }
    QFile outFile("log.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << QTime::currentTime().toString() << "# " << txt << "\n";
}


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

    QFile::remove("log.txt");

    qInstallMessageHandler(myMessageHandler);

    qmlRegisterSingletonType(QUrl("qrc:/qml/StyleSettings.qml"), "StyleSettings", 1, 0, "Style");
    qmlRegisterType<SweepChart>("SweepChart", 1, 0, "SweepChart");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
            {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);

    AppEngine appEngine;

    engine.rootContext()->setContextProperty("appEngine", &appEngine);

    engine.load(url);

    return app.exec();
}
