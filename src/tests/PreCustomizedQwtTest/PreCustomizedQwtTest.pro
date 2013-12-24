#-------------------------------------------------
#
# Project created by QtCreator 2013-12-18T13:48:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PreCustomizedQwtTest
TEMPLATE = app

CONFIG += c++11 qwt

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/PreCustomizedQwt/release/ -lPreCustomizedQwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/PreCustomizedQwt/debug/ -lPreCustomizedQwt
else:unix:!macx: LIBS += -L$$OUT_PWD/../../libs/PreCustomizedQwt/ -lPreCustomizedQwt

INCLUDEPATH += $$PWD/../../libs/PreCustomizedQwt
DEPENDPATH += $$PWD/../../libs/PreCustomizedQwt
#Include qwt library after PreCustomizedQwt
include($$PWD/../../auxiliary/qwtPath.pri)
