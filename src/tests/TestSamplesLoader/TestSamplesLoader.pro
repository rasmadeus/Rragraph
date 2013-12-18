#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T15:40:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestSamplesLoader
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    SamplesViewer.cpp

HEADERS  += \
    SamplesViewer.h

FORMS    += \
    SamplesViewer.ui



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/FilesLoader/release/ -lFilesLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/FilesLoader/debug/ -lFilesLoader
else:unix:!macx: LIBS += -L$$OUT_PWD/../../libs/FilesLoader/ -lFilesLoader

INCLUDEPATH += $$PWD/../../libs/FilesLoader
DEPENDPATH += $$PWD/../../libs/FilesLoader
