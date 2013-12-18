z#-------------------------------------------------
#
# Project created by QtCreator 2013-09-16T21:06:42
#
#-------------------------------------------------

QT       += core gui svg printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rragraph
TEMPLATE = app
CONFIG   += c++11
DESTDIR = $$PWD/../../installer/packages/plotter/data

win32{
    RC_FILE = res/icon.rc
}

TRANSLATIONS += $$PWD/translations/ru.ts \
    $$PWD/translations/kr.ts \
    $$PWD/translations/ar.ts

include ($$PWD/FilesLoader.pri)
include ($$PWD/Plot.pri)
include ($$PWD/Auxiliary.pri)
include ($$PWD/Headers.pri)
include ($$PWD/PlotSettingsGui.pri)
include ($$PWD/CurveSettings.pri)

SOURCES += main.cpp \
    MainWindow.cpp \
    MdiArea.cpp \
    Project.cpp \
    MdiAreaRearranger.cpp \
    Translator.cpp \
    ExitMessage.cpp

HEADERS  += \
    MainWindow.h \
    MdiArea.h \
    Project.h \
    Translator.h \
    ExitMessage.h

FORMS += \
    MainWindow.ui \
    ExitMessage.ui

RESOURCES += \
    res.qrc
