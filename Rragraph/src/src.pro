#-------------------------------------------------
#
# Project created by QtCreator 2013-09-16T21:06:42
#
#-------------------------------------------------

QT       += core gui svg quick printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
TEMPLATE = app
CONFIG   += c++11

include ($$PWD/FilesLoader.pri)
include ($$PWD/Plot.pri)
include ($$PWD/Auxiliary.pri)
include ($$PWD/Headers.pri)
include ($$PWD/PlotSettingsGui.pri)
include ($$PWD/CurveSettings.pri)

SOURCES += main.cpp \
    MainWindow.cpp \
    MdiArea.cpp \
    Project.cpp

HEADERS  += \
    MainWindow.h \
    MdiArea.h \
    Project.h

FORMS += \
    MainWindow.ui

RESOURCES += \
    res.qrc

OTHER_FILES +=
