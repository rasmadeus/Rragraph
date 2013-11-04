unix{
    LIBS += -L$$PWD/../../../../../../Programs/Qt/Qwt-6.1.0/lib/ -lqwt
    INCLUDEPATH += $$PWD/../../../../../../Programs/Qt/Qwt-6.1.0/include
    DEPENDPATH += $$PWD/../../../../../../Programs/Qt/Qwt-6.1.0/include
    PRE_TARGETDEPS += $$PWD/../../../../../../Programs/Qt/Qwt-6.1.0/lib/libqwt.a
}

HEADERS += \
    Canvas.h \
    Grid.h \
    Plot.h \
    Zoomer.h \
    LegendItem.h \
    Curve.h \
    Exporter.h

SOURCES += \
    Canvas.cpp \
    Grid.cpp \
    Plot.cpp \
    Zoomer.cpp \
    LegendItem.cpp \
    Curve.cpp \
    Exporter.cpp
