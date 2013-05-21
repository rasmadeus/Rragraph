#include "RecentlyClosed.h"

RecentlyClosed::RecentlyClosed(QMenu* menu, QObject *parent) :
    QObject(parent),
    menu(menu)
{
}

#include <QSettings>
void RecentlyClosed::fill(QSettings& settings)
{
    settings.beginGroup("RecentlyClosed");
        updateRecentlyClosedMenu(readRecentlyClosed(settings));
    settings.endGroup();
}

void RecentlyClosed::savePathOfProject(const QString& projectName)
{
    QSettings settings;
    settings.beginGroup("Widget settings/MainWindow/RecentlyClosed");
    QList<QString> paths = readRecentlyClosed(settings);
        paths.removeAll(projectName);
        if(paths.size() > 30) paths.removeLast();
        paths.insert(0, projectName);
    writeRecentlyClosed(paths, settings);
    updateRecentlyClosedMenu(paths);
    settings.endGroup();
}

#include <QStringList>
QList<QString> RecentlyClosed::readRecentlyClosed(QSettings &settings)
{
    QList<QString> paths;
    foreach(QString key, settings.childKeys())
        paths.append(settings.value(key).toString());
    return paths;
}

void RecentlyClosed::writeRecentlyClosed(const QList<QString> &paths, QSettings& settings)
{
    foreach(QString key, settings.childKeys()) settings.remove(key);
    for(int i=0; i<paths.size(); ++i) settings.setValue(QString("%1").arg(i), paths[i]);
}

#include <QAction>
#include <QMenu>
void RecentlyClosed::updateRecentlyClosedMenu(const QList<QString> &paths)
{
//Delete old actions;
    QAction* temp = menu->actions().last();
    foreach(QAction* action, menu->actions()){
        if(action != temp) menu->removeAction(action);
    }
//Add new actions
    foreach(QString path, paths){
        QAction* action = new QAction(path, menu);
        connect(action, SIGNAL(triggered()), this, SLOT(recentlyClosedActionTriggered()));
        menu->insertAction(temp, action);
    }
//Insert separator
    menu->insertSeparator(temp);
}

#include <QFileInfo>
void RecentlyClosed::removeNonexistentPaths()
{
    QSettings settings;
    settings.beginGroup("Widget settings/MainWindow/RecentlyClosed");
        QList<QString> paths = readRecentlyClosed(settings);
        foreach(QString path, paths){
            if(!QFileInfo(path).isReadable()) paths.removeOne(path);
        }
        writeRecentlyClosed(paths, settings);
        updateRecentlyClosedMenu(paths);
    settings.endGroup();
}

void RecentlyClosed::recentlyClosedActionTriggered()
{
    QAction* action = qobject_cast<QAction*>(sender());
    if(action){
        emit readProjectFrom(action->text());
    }
}
