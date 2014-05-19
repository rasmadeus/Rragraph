#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T10:45:53
#
#-------------------------------------------------

QT       += core printsupport

QT       -= gui

TARGET = TestConverter
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/VersionConverter/release/ -lVersionConverter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/VersionConverter/debug/ -lVersionConverter
else:unix: LIBS += -L$$OUT_PWD/../../libs/VersionConverter/ -lVersionConverter

INCLUDEPATH += $$PWD/../../libs/VersionConverter
DEPENDPATH += $$PWD/../../libs/VersionConverter
