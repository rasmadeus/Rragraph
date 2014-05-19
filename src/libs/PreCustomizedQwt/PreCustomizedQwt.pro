#-------------------------------------------------
#
# Project created by QtCreator 2013-12-19T09:49:38
#
#-------------------------------------------------

QT       += widgets svg printsupport

TARGET = PreCustomizedQwt
TEMPLATE = lib
CONFIG += staticlib c++11 qwt

include($$PWD/../../auxiliary/qwtPath.pri)
include($$PWD/PlotSettings.pri)

SOURCES += \
    Plot.cpp \
    LegendItem.cpp \
    Grid.cpp \
    Curve.cpp \
    Canvas.cpp \
    Zoomer.cpp

HEADERS += \
    Plot.h \
    LegendItem.h \
    Grid.h \
    Curve.h \
    Canvas.h \
    Zoomer.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FilesLoader/release/ -lFilesLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FilesLoader/debug/ -lFilesLoader
else:unix: LIBS += -L$$OUT_PWD/../FilesLoader/ -lFilesLoader

INCLUDEPATH += $$PWD/../FilesLoader
DEPENDPATH += $$PWD/../FilesLoader
