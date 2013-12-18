unix{
    LIBS += -L$$PWD/../../../../../../Programs/Qt/Qwt-6.1.0/lib/ -lqwt
    INCLUDEPATH += $$PWD/../../../../../../Programs/Qt/Qwt-6.1.0/include
    DEPENDPATH += $$PWD/../../../../../../Programs/Qt/Qwt-6.1.0/include
    PRE_TARGETDEPS += $$PWD/../../../../../../Programs/Qt/Qwt-6.1.0/lib/libqwt.a
}

win32{
    include(c:\Dev\Qt5.1.1\Qwt-6.1.0\features\qwt.prf)
}