#-------------------------------------------------
#
# Project created by QtCreator 2013-12-10T09:00:29
#
#-------------------------------------------------

QT       += widgets core printsupport


QT       -= gui

TARGET = SamplesThreadTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/FilesLoader/release/ -lFilesLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/FilesLoader/debug/ -lFilesLoader
else:unix:!macx: LIBS += -L$$OUT_PWD/../../libs/FilesLoader/ -lFilesLoader

INCLUDEPATH += $$PWD/../../libs/FilesLoader
DEPENDPATH += $$PWD/../../libs/FilesLoader
