#-------------------------------------------------
#
# Project created by QtCreator 2014-01-13T23:24:08
#
#-------------------------------------------------

QT       += widgets

TARGET = CurvesManager
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += \
    Curves.cpp \
    CurvesManagerView.cpp \
    CurvesManager.cpp

HEADERS += \
    Curves.h \
    CurvesManagerView.h \
    CurvesManager.h

include(CurveSettings.pri)
include(CurvesFiller.pri)
include($$PWD/../../auxiliary/qwtPath.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../FilesLoader/release/ -lFilesLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../FilesLoader/debug/ -lFilesLoader
else:unix:!macx: LIBS += -L$$OUT_PWD/../FilesLoader/ -lFilesLoader

INCLUDEPATH += $$PWD/../FilesLoader
DEPENDPATH += $$PWD/../FilesLoader

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FilesLoader/release/libFilesLoader.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FilesLoader/debug/libFilesLoader.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FilesLoader/release/FilesLoader.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../FilesLoader/debug/FilesLoader.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../FilesLoader/libFilesLoader.a


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PreCustomizedQwt/release/ -lPreCustomizedQwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PreCustomizedQwt/debug/ -lPreCustomizedQwt
else:unix:!macx: LIBS += -L$$OUT_PWD/../PreCustomizedQwt/ -lPreCustomizedQwt

INCLUDEPATH += $$PWD/../PreCustomizedQwt
DEPENDPATH += $$PWD/../PreCustomizedQwt

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PreCustomizedQwt/release/libPreCustomizedQwt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PreCustomizedQwt/debug/libPreCustomizedQwt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PreCustomizedQwt/release/PreCustomizedQwt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PreCustomizedQwt/debug/PreCustomizedQwt.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../PreCustomizedQwt/libPreCustomizedQwt.a

FORMS += \
    CurvesManagerView.ui
