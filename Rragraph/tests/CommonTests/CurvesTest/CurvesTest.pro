#-------------------------------------------------
#
# Project created by QtCreator 2013-09-29T22:49:50
#
#-------------------------------------------------

QT       += core gui svg printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurvesTest
TEMPLATE = app
CONFIG   += c++11
unix{
    LIBS += -L$$PWD/../../../../../../../../Programs/Qt/Qwt-6.1.0/lib/ -lqwt
    INCLUDEPATH += $$PWD/../../../../../../../../Programs/Qt/Qwt-6.1.0/include
    DEPENDPATH += $$PWD/../../../../../../../../Programs/Qt/Qwt-6.1.0/include
    PRE_TARGETDEPS += $$PWD/../../../../../../../../Programs/Qt/Qwt-6.1.0/lib/libqwt.a
}


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../../src/Canvas.cpp \
    ../../../src/Curve.cpp \
    ../../../src/Plot.cpp \
    ../../../src/LegendItem.cpp \
    ../../../src/Grid.cpp \
    ../../../src/Zoomer.cpp \
    ../../../src/CurveSettingsView.cpp \
    ../../../src/Files.cpp \
    ../../../src/FilesModel.cpp \
    ../../../src/Samples.cpp \
    ../../../src/Loader.cpp \
    ../../../src/Curves.cpp \
    ../../../src/HeaderSamples.cpp \
    ../../../src/CurvesModel.cpp \
    ../../../src/DoubleDelegate.cpp \
    ../../../src/CurveSettings.cpp \
    ../../../src/RestorablePath.cpp \
    ../../../src/Saveable.cpp

HEADERS  += mainwindow.h \
    ../../../src/Curve.h \
    ../../../src/Canvas.h \
    ../../../src/Plot.h \
    ../../../src/LegendItem.h \
    ../../../src/Grid.h \
    ../../../src/global.h \
    ../../../src/Savable.h \
    ../../../src/Zoomer.h \
    ../../../src/CurveSettingsView.h \
    ../../../src/Files.h \
    ../../../src/FilesModel.h \
    ../../../src/Samples.h \
    ../../../src/Loader.h \
    ../../../src/Curves.h \
    ../../../src/HeaderSamples.h \
    ../../../src/CurvesModel.h \
    ../../../src/DoubleDelegate.h \
    ../../../src/CurveSettings.h \
    ../../../src/RestorablePath.h

FORMS    += mainwindow.ui \
    ../../../src/CurveSettingsView.ui \
    ../../../src/CurveSettings.ui

OTHER_FILES += \
    ../../../Rragraph.pro
