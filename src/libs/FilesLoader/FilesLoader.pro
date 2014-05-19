#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T14:09:47
#
#-------------------------------------------------

QT       += widgets core

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



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Settings/release/ -lSettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Settings/debug/ -lSettings
else:unix:!macx: LIBS += -L$$OUT_PWD/../Settings/ -lSettings

INCLUDEPATH += $$PWD/../Settings
DEPENDPATH += $$PWD/../Settings

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Settings/release/libSettings.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Settings/debug/libSettings.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Settings/release/Settings.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Settings/debug/Settings.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Settings/libSettings.a
