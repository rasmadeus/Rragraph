#-------------------------------------------------
#
# Project created by QtCreator 2014-01-18T21:03:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SamplesManagerViewTest
TEMPLATE = app


SOURCES += main.cpp

HEADERS  +=

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/FilesLoader/release/ -lFilesLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/FilesLoader/debug/ -lFilesLoader
else:unix: LIBS += -L$$OUT_PWD/../../libs/FilesLoader/ -lFilesLoader

INCLUDEPATH += $$PWD/../../libs/FilesLoader
DEPENDPATH += $$PWD/../../libs/FilesLoader

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/FilesLoader/release/libFilesLoader.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/FilesLoader/debug/libFilesLoader.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/FilesLoader/release/FilesLoader.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/FilesLoader/debug/FilesLoader.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../libs/FilesLoader/libFilesLoader.a
