QT += quick gui core widgets qml charts serialport multimedia

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    src/AppEngine.h \
    src/SweepChart.h \
    src/SweepChartBuffer.h


SOURCES += \        
        src/AppEngine.cpp \
        src/SweepChart.cpp \
        src/SweepChartBuffer.cpp \
        src/main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

build_dir = $$_PRO_FILE_PWD_/build
DESTDIR = $$build_dir
PRECOMPILED_DIR = $$build_dir

#нужна для сборки внутренних библиотек qt, для решения конфликтов необходимо добавить qt в PATH
CONFIG(debug, debug|release): win32:QMAKE_POST_LINK += windeployqt.exe --qmldir $$_PRO_FILE_PWD_/qml $$DESTDIR/ECG_URAL.exe

OBJECTS_DIR = $$build_dir/trash/obj
MOC_DIR     = $$build_dir/trash/moc
RCC_DIR     = $$build_dir/trash/rcc
UI_DIR      = $$build_dir/trash/ui


