#include "Guide.h"

Guide::Guide(QObject *parent) :
    QThread(parent)
{
}

#include <QAction>
#include <QApplication>
void Guide::setUrl(QAction *action)
{
    url = "file:///" + qApp->applicationDirPath() + "/guide/" + action->data().toString() + "/index.html";
}

#include <QDesktopServices>
void Guide::run()
{
    QDesktopServices::openUrl(url);
    emit dataWasShowed();
}
