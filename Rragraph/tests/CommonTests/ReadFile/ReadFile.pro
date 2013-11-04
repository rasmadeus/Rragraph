#-------------------------------------------------
#
# Project created by QtCreator 2013-09-14T12:52:51
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = ReadFile
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += ReadFile.cpp \
    ../../../src/Saveable.cpp \
    ../../../src/Samples.cpp \
    ../../../src/Loader.cpp \
    ../../../src/RestorablePath.cpp

HEADERS += \
    ../../../global.h \
    ../../../src/Savable.h \
    ../../../src/Samples.h \
    ../../../src/Loader.h \
    ../../../src/RestorablePath.h


