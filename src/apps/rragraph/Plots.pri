
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/PreCustomizedQwt/release/ -lPreCustomizedQwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/PreCustomizedQwt/debug/ -lPreCustomizedQwt
else:unix: LIBS += -L$$OUT_PWD/../../libs/PreCustomizedQwt/ -lPreCustomizedQwt

INCLUDEPATH += $$PWD/../../libs/PreCustomizedQwt
DEPENDPATH += $$PWD/../../libs/PreCustomizedQwt

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/PreCustomizedQwt/release/libPreCustomizedQwt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/PreCustomizedQwt/debug/libPreCustomizedQwt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/PreCustomizedQwt/release/PreCustomizedQwt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libs/PreCustomizedQwt/debug/PreCustomizedQwt.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../libs/PreCustomizedQwt/libPreCustomizedQwt.a

include($$PWD/../../auxiliary/qwtPath.pri)

HEADERS += \
    PlotWithCurves.h \
    Group.h

SOURCES += \
    PlotsRearranger.cpp \
    PlotWithCurves.cpp \
    Group.cpp
