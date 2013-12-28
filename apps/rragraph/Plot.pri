unix{
    include(/home/rasmadeus/Programs/Qt/qwt-6.1.0/features/qwt.prf)
}

win32{
    include(c:\Dev\Qt5.1.1\Qwt-6.1.0\features\qwt.prf)
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
