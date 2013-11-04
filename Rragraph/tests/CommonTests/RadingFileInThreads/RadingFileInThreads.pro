#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T19:42:32
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = RadingFileInThreads
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../../src/Loader.cpp \
    ../../../src/Samples.cpp \
    Consumer.cpp \
    ../../../src/RestorablePath.cpp

HEADERS += \
    ../../../src/Loader.h \
    ../../../src/Samples.h \
    Consumer.h \
    ../../../src/RestorablePath.h

OTHER_FILES += \
    ../../../Rragraph.pro
