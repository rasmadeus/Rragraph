#-------------------------------------------------
#
# Project created by QtCreator 2013-09-22T12:10:07
#
#-------------------------------------------------

QT       += core gui printsupport
QT       += svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LegendItemTest
TEMPLATE = app
CONFIG   += c++11

SOURCES += main.cpp \
    ../../../src/Canvas.cpp \
    ../../../src/Grid.cpp \
    ../../../src/Plot.cpp \
    ../../../src/Zoomer.cpp \
    ../../../src/LegendItem.cpp \
    ../../../src/CurveSettingsView.cpp \
    ../../../src/Files.cpp \
    ../../../src/FilesModel.cpp \
    ../../../src/Samples.cpp \
    ../../../src/Loader.cpp \
    ../../../src/Curves.cpp \
    ../../../src/Curve.cpp \
    ../../../src/HeaderSamples.cpp \
    ../../../src/CurvesModel.cpp \
    ../../../src/DoubleDelegate.cpp \
    ../../../src/CurveSettings.cpp \
    ../../../src/RestorablePath.cpp \
    ../../../src/Saveable.cpp

HEADERS  += \
    ../../../src/Canvas.h \
    ../../../src/Grid.h \
    ../../../src/global.h \
    ../../../src/Plot.h \
    ../../../src/Zoomer.h \
    ../../../src/LegendItem.h \
    ../../../src/CurveSettingsView.h \
    ../../../src/Files.h \
    ../../../src/FilesModel.h \
    ../../../src/Samples.h \
    ../../../src/Loader.h \
    ../../../src/Curves.h \
    ../../../src/Curve.h \
    ../../../src/HeaderSamples.h \
    ../../../src/CurvesModel.h \
    ../../../src/DoubleDelegate.h \
    ../../../src/CurveSettings.h \
    ../../../src/RestorablePath.h \
    ../../../src/Savable.h


unix{
    LIBS += -L$$PWD/../../../../../../../../Programs/Qt/Qwt-6.1.0/lib/ -lqwt
    INCLUDEPATH += $$PWD/../../../../../../../../Programs/Qt/Qwt-6.1.0/include
    DEPENDPATH += $$PWD/../../../../../../../../Programs/Qt/Qwt-6.1.0/include
    PRE_TARGETDEPS += $$PWD/../../../../../../../../Programs/Qt/Qwt-6.1.0/lib/libqwt.a
}

FORMS += \
    ../../../src/CurveSettingsView.ui \
    ../../../src/CurveSettings.ui
