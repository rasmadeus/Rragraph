#-------------------------------------------------
#
# Project created by QtCreator 2014-01-18T18:14:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11 qwt
TARGET = CurvesManagerTest
TEMPLATE = app

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../libs/FilesLoader/release/ -lFilesLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../libs/FilesLoader/debug/ -lFilesLoader
else:unix: LIBS += -L$$OUT_PWD/../../../libs/FilesLoader/ -lFilesLoader

INCLUDEPATH += $$PWD/../../../libs/FilesLoader
DEPENDPATH += $$PWD/../../../libs/FilesLoader

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/FilesLoader/release/libFilesLoader.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/FilesLoader/debug/libFilesLoader.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/FilesLoader/release/FilesLoader.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/FilesLoader/debug/FilesLoader.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../../libs/FilesLoader/libFilesLoader.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../libs/CurvesManager/release/ -lCurvesManager
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../libs/CurvesManager/debug/ -lCurvesManager
else:unix: LIBS += -L$$OUT_PWD/../../../libs/CurvesManager/ -lCurvesManager

INCLUDEPATH += $$PWD/../../../libs/CurvesManager
DEPENDPATH += $$PWD/../../../libs/CurvesManager

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/CurvesManager/release/libCurvesManager.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/CurvesManager/debug/libCurvesManager.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/CurvesManager/release/CurvesManager.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/CurvesManager/debug/CurvesManager.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../../libs/CurvesManager/libCurvesManager.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../libs/PreCustomizedQwt/release/ -lPreCustomizedQwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../libs/PreCustomizedQwt/debug/ -lPreCustomizedQwt
else:unix: LIBS += -L$$OUT_PWD/../../../libs/PreCustomizedQwt/ -lPreCustomizedQwt

INCLUDEPATH += $$PWD/../../../libs/PreCustomizedQwt
DEPENDPATH += $$PWD/../../../libs/PreCustomizedQwt

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/PreCustomizedQwt/release/libPreCustomizedQwt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/PreCustomizedQwt/debug/libPreCustomizedQwt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/PreCustomizedQwt/release/PreCustomizedQwt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/PreCustomizedQwt/debug/PreCustomizedQwt.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../../libs/PreCustomizedQwt/libPreCustomizedQwt.a
include($$PWD/../../../auxiliary/qwtPath.pri)
