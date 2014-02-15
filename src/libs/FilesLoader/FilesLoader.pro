#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T14:09:47
#
#-------------------------------------------------

QT       += widgets

TARGET = FilesLoader
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += \
    Samples.cpp \
    SamplesManager.cpp \
    SamplesManagerModel.cpp \
    SamplesManagerView.cpp \
    ListModel.cpp \
    Path.cpp \
    SamplesProxyModel.cpp \
    SamplesProxyView.cpp \
    DoubleDelegate.cpp \
    StringDelegate.cpp

HEADERS += \
    Samples.h \
    SamplesManager.h \
    SamplesManagerModel.h \
    SamplesManagerView.h \
    ListModel.h \
    Path.h \
    SamplesProxyModel.h \
    SamplesProxyView.h \
    DoubleDelegate.h \
    StringDelegate.h

FORMS += \
    SamplesManagerView.ui \
    SamplesProxyView.ui
