#-------------------------------------------------
#
# Project created by QtCreator 2013-12-18T13:48:52
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PreCustomizedQwtTest
TEMPLATE = app

CONFIG += c++11 qwt printsupport

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/FilesLoader/release/ -lFilesLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/FilesLoader/debug/ -lFilesLoader
else:unix: LIBS += -L$$OUT_PWD/../../libs/FilesLoader/ -lFilesLoader

INCLUDEPATH += $$PWD/../../libs/FilesLoader
DEPENDPATH += $$PWD/../../libs/FilesLoader

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/Settings/release/ -lSettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/Settings/debug/ -lSettings
else:unix: LIBS += -L$$OUT_PWD/../../libs/Settings/ -lSettings

INCLUDEPATH += $$PWD/../../libs/Settings
DEPENDPATH += $$PWD/../../libs/Settings

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/Settings/release/libSettings.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/Settings/debug/libSettings.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/Settings/release/Settings.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/Settings/debug/Settings.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../libs/Settings/libSettings.a
