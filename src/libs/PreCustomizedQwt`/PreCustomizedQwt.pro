#-------------------------------------------------
#
# Project created by QtCreator 2013-12-19T09:36:37
#
#-------------------------------------------------

QT       += widgets opengl svg

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = PreCusomizedQwt
TEMPLATE = lib
CONFIG += staticlib c++11 qwt

include($$PWD/../../auxiliary/qwtPath.pri)

SOURCES += \
    Zoomer.cpp \
    Plot.cpp \
    LegendItem.cpp \
    Grid.cpp \
    Curve.cpp \
    Canvas.cpp

HEADERS += \
    Zoomer.h \
    Plot.h \
    LegendItem.h \
    Grid.h \
    Curve.h \
    Canvas.h
