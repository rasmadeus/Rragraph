#-------------------------------------------------
#
# Project created by QtCreator 2013-12-19T09:49:38
#
#-------------------------------------------------

QT       += widgets svg

TARGET = PreCustomizedQwt
TEMPLATE = lib
CONFIG += staticlib c++11

include($$PWD/../../auxiliary/qwtPath.pri)

SOURCES += \
    Plot.cpp \
    LegendItem.cpp \
    Grid.cpp \
    Curve.cpp \
    Canvas.cpp \
    Zoomer.cpp

HEADERS += \
    Plot.h \
    LegendItem.h \
    Grid.h \
    Curve.h \
    Canvas.h \
    Zoomer.h

