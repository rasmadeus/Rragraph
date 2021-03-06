#include "RecentlyProjectPaths.h"

RecentlyProjectPaths::RecentlyProjectPaths(QObject *parent) :
    QActionGroup(parent)
{
}

void RecentlyProjectPaths::update(QMenu* projectMenu)
{
    clear();
    fill(projectMenu);
}

void RecentlyProjectPaths::clear()
{
    foreach (QAction* action, actions()) {
        removeAction(action);
    }
}

#include <QMenu>
void RecentlyProjectPaths::fill(QMenu* projectMenu)
{
    const QStringList recentlyProPaths = getExistPaths();
    if(!recentlyProPaths.isEmpty()){
        projectMenu->addSeparator();
        foreach(const QString& recentlyProPath, recentlyProPaths){
            QAction* action = new QAction(reducePath(recentlyProPath), this);
            action->setStatusTip(recentlyProPath);
            action->setData(recentlyProPath);
            addAction(action);
        }
        projectMenu->addActions(actions());
        projectMenu->addSeparator();
    }
}

QString RecentlyProjectPaths::reducePath(const QString& path) const
{
    QStringList parts = path.split("/");
    if(parts.size() >= 2){
        return ".../" + parts[parts.size() - 2] + "/" + parts[parts.size() - 1];
    }
    return path;
}

#include <Settings.h>
#include <QFileInfo>
#include <QApplication>
QStringList RecentlyProjectPaths::getExistPaths() const
{
    QStringList recentlyProPaths;
    const int n = Settings::obj()->get().beginReadArray("recentlyProPaths");
    for(int i = 0; i< n; ++i){
        Settings::obj()->get().setArrayIndex(i);
        const QString proFile = Settings::obj()->get("path").toString();
        if(QFileInfo(proFile).exists()){
            recentlyProPaths << proFile;
        }
    }
    Settings::obj()->get().endArray();
    return recentlyProPaths;
}

void RecentlyProjectPaths::appendPath(const QString& pathToPro)
{
    QStringList recenlyProPaths = getExistPaths();
    if(recenlyProPaths.contains(pathToPro)){
        recenlyProPaths.removeOne(pathToPro);
    }
    if(recenlyProPaths.size() == 5){//Show in menu only 5 items.
        recenlyProPaths.removeLast();
    }
    recenlyProPaths.push_front(pathToPro);
    write(recenlyProPaths);
}

void RecentlyProjectPaths::write(const QStringList& recenlyProPaths)
{

    Settings::obj()->get().beginWriteArray("recentlyProPaths");
        for(int i = 0; i < recenlyProPaths.size(); ++i){
            Settings::obj()->get().setArrayIndex(i);
            Settings::obj()->set("path", recenlyProPaths[i]);
        }
    Settings::obj()->get().endArray();
}
