#-------------------------------------------------
#
# Project created by QtCreator 2013-03-19T14:56:46
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = FilePathParsingTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += FilePathParsingTest.cpp \
    ../../Canvas/Data/FilePathParsing/FilePathParsing.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../Canvas/Data/FilePathParsing/FilePathParsing.h


