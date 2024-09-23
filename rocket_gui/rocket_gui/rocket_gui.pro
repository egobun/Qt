QT +=  core gui serialport
QT+= core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SerialPort.cpp \
    dataprocessor.cpp \
    main.cpp \
    mainwindow.cpp \
    pitchwindow.cpp \
    qcustomplot.cpp \
    rollwindow.cpp

HEADERS += \
    SerialPort.h \
    dataprocessor.h \
    mainwindow.h \
    pitchwindow.h \
    qcustomplot.h \
    rollwindow.h

FORMS += \
    mainwindow.ui \
    pitchwindow.ui \
    rollwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
