#include <QtGui/QGuiApplication>
#include "QuickViewer.h"


#include "SamplesManager.h"
#include "Manager.h"
#include <QQuickItem>
#include <QQmlContext>
int main(int argc, char* argv[])
{
    QGuiApplication higraph(argc, argv);

    QuickViewer viewer;
    viewer.setMainQmlFile("qml/higraph/main.qml");
    viewer.showMaximized();

    new Manager(viewer.rootObject());
    viewer.rootContext();

    return higraph.exec();
}
