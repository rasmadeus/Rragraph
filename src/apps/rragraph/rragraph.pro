#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T14:06:39
#
#-------------------------------------------------

QT       += core gui printsupport
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rragraph
TEMPLATE = app

DESTDIR = $$PWD/../../../installer/rragraph/windows_xp_32

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/CurvesManager/release/ -lCurvesManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/CurvesManager/debug/ -lCurvesManager
else:unix: LIBS += -L$$OUT_PWD/../../libs/CurvesManager/ -lCurvesManager

INCLUDEPATH += $$PWD/../../libs/CurvesManager
DEPENDPATH += $$PWD/../../libs/CurvesManager

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/CurvesManager/release/libCurvesManager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/CurvesManager/debug/libCurvesManager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/CurvesManager/release/CurvesManager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/CurvesManager/debug/CurvesManager.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../libs/CurvesManager/libCurvesManager.a

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

include($$PWD/Groups.pri)
include($$PWD/PlotWithCurves.pri)
include($$PWD/Project.pri)
include($$PWD/Messages.pri)

SOURCES += main.cpp\
    MainWindow.cpp \
    Translator.cpp

HEADERS  += MainWindow.h \
    Translator.h

FORMS    += MainWindow.ui

RESOURCES += \
    res.qrc

TRANSLATIONS += $$PWD/ts/app_ru.ts

win32{
    RC_FILE = $$PWD/res/icon.rc
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/Settings/release/ -lSettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/Settings/debug/ -lSettings
else:unix:!macx: LIBS += -L$$OUT_PWD/../../libs/Settings/ -lSettings

INCLUDEPATH += $$PWD/../../libs/Settings
DEPENDPATH += $$PWD/../../libs/Settings
