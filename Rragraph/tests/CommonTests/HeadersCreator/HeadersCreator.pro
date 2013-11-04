#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T22:16:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = HeadersCreator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
CONFIG   += c++11

SOURCES += HeadersCreator.cpp \
    ../../../src/RestorablePath.cpp \
    ../../../src/Saveable.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../src/RestorablePath.h \
    ../../../src/Savable.h

