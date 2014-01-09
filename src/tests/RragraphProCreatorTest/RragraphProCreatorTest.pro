#-------------------------------------------------
#
# Project created by QtCreator 2013-12-30T21:30:28
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = RragraphProCreatorTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/RragraphProCreator/release/ -lRragraphProCreator
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/RragraphProCreator/debug/ -lRragraphProCreator
else:unix:!macx: LIBS += -L$$OUT_PWD/../../libs/RragraphProCreator/ -lRragraphProCreator

INCLUDEPATH += $$PWD/../../libs/RragraphProCreator
DEPENDPATH += $$PWD/../../libs/RragraphProCreator

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/RragraphProCreator/release/libRragraphProCreator.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/RragraphProCreator/debug/libRragraphProCreator.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/RragraphProCreator/release/RragraphProCreator.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/RragraphProCreator/debug/RragraphProCreator.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../libs/RragraphProCreator/libRragraphProCreator.a
