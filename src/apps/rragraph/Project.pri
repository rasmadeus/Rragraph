HEADERS += \
    Project.h \
    RecentlyProjectPaths.h

SOURCES += \
    Project.cpp \
    RecentlyProjectPaths.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/VersionConverter/release/ -lVersionConverter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/VersionConverter/debug/ -lVersionConverter
else:unix: LIBS += -L$$OUT_PWD/../../libs/VersionConverter/ -lVersionConverter

INCLUDEPATH += $$PWD/../../libs/VersionConverter
DEPENDPATH += $$PWD/../../libs/VersionConverter
