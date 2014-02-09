
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
    PlotSettingsView.h \
    PlotSettings.h \
    CommonPlotSettings.h \
    AxisPlotSettings.h \
    ExportPlotSettings.h \
    LegendPlotSettings.h \
    FontColorSettingsAble.h \
    GroupSettings.h

SOURCES += \
    PlotWithCurves.cpp \
    PlotSettingsView.cpp \ 
    PlotSettings.cpp \
    CommonPlotSettings.cpp \
    AxisPlotSettings.cpp \
    ExportPlotSettings.cpp \
    LegendPlotSettings.cpp \
    FontColorSettingsAble.cpp \
    GroupSettings.cpp

FORMS += \
    PlotSettingsView.ui \
    CommonPlotSettings.ui \
    AxisPlotSettings.ui \
    ExportPlotSettings.ui \
    LegendPlotSettings.ui \
    GroupSettings.ui

