#-------------------------------------------------
#
# Project created by QtCreator 2013-12-17T09:54:47
#
#-------------------------------------------------

QT       += widgets

TARGET = PreCustomizedQwt
TEMPLATE = lib
CONFIG += staticlib c++11

include($$PWD/../../auxiliary/qwtPath.pri)

SOURCES += \
    Plot.cpp \
    LegendItem.cpp \
    Grid.cpp \
    Zoomer.cpp \
    Canvas.cpp \
    Curve.cpp

HEADERS += \
    Plot.h \
    LegendItem.h \
    Grid.h \
    Zoomer.h \
    Canvas.h \
    Curve.h
