# Add more folders to ship with the application, here
folder_01.source = qml/higraph
folder_01.target = qml
installFolder.source = qml/higraph
installFolder.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

# Installation path
TARGET = Higraph

# Please do not modify the following two lines. Required for deployment.
include(quickViewer/quickViewer.pri)
qtcAddDeployment()

win32{
    RC_FILE = res/icon.rc
}

CONFIG += c++11

include(QmlToObject.pri)

RESOURCES += \
    res.qrc

QT       += widgets core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/FilesLoader/release/ -lFilesLoader
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/FilesLoader/debug/ -lFilesLoader
else:unix: LIBS += -L$$OUT_PWD/../../libs/FilesLoader/ -lFilesLoader

INCLUDEPATH += $$PWD/../../libs/FilesLoader
DEPENDPATH += $$PWD/../../libs/FilesLoader


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libs/Settings/release/ -lSettings
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libs/Settings/debug/ -lSettings
else:unix:!macx: LIBS += -L$$OUT_PWD/../../libs/Settings/ -lSettings

INCLUDEPATH += $$PWD/../../libs/Settings
DEPENDPATH += $$PWD/../../libs/Settings

