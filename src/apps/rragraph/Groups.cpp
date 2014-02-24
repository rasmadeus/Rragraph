#include "Groups.h"

Path Groups::exportPath("appSettings.ini", "paths/exportPath");

Groups::Groups(QWidget* parent) :
    QTabWidget(parent)
{
    setStyles();
    setLookAndFeel();
    setFocusPolicy(Qt::NoFocus);
    connect(this, SIGNAL(tabCloseRequested(int)), SLOT(closeGroup(int)));
    connect(this, SIGNAL(currentChanged(int)), SLOT(createGroupChangedSignal(int)));
}

void Groups::setStyles()
{
    setStyleSheet(
        "QTabBar::tab{"
            "background: qlineargradient("
                "x1: 0, y1: 0, x2: 0, y2: 1,"
                "stop: 0 #fafafa,"
                "stop: 0.4 #f4f4f4,"
                "stop: 0.5 #e7e7e7,"
                "stop: 1.0 #fafafa"
            ");"
            "border-bottom-right-radius: 6px;"
            "border-top-right-radius: 6px;"
            "min-height: 8ex;"
            "width: 15px;"
            "padding: 2px;"
            "border: 1px solid #C4C4C3;"
        "}"

        "QTabBar::tab:selected{"
            "background: qlineargradient("
                "x1: 0, y1: 0, x2: 1, y2: 0,"
                "stop: 0 #777777,"
                "stop: 0.25 #999999,"
                "stop: 0.5 #aaaaaa,"
                "stop: 0.75 #cccccc,"
                "stop: 1.0 #dddddd"
            ");"
        "}"

        "QTabBar::tab:hover{"
            "border: 1px solid #000;"
        "}"
    );
}

void Groups::setLookAndFeel()
{
    setTabsClosable(true);
    setMovable(true);
    setUsesScrollButtons(true);
    setTabPosition(East);
}

#include "Group.h"
Group* Groups::addGroup()
{
    Group* group = new Group(this);
    groups << group;
    addTab(group, "");
    retitle();    
    if(count() == 1){
        emit hasGroups(true);
    }
    setCurrentIndex(count() - 1);
    connect(group, SIGNAL(subWindowActivated(QMdiSubWindow*)), SIGNAL(wasActivated(QMdiSubWindow*)));
    return group;
}

void Groups::retranslate()
{
    retitle();
    foreach(Group* group, groups){
        group->retranslate();
    }
}

void Groups::closeGroup(int i)
{
    removeTab(i);
    delete groups[i];
    groups.remove(i);
    retitle();
    if(groups.isEmpty()){
        emit hasGroups(false);
        emit noMoreGroup();
    }
}

void Groups::closeGroups()
{
    while(!groups.isEmpty()){
        closeGroup(0);
    }
}

void Groups::retitle()
{
    int iName = 0;
    for(int i = 0; i < count(); ++i){
        const QString tabText(
            groups[i]->nameIsEmpty()     ?
            tr("Group") +  QString(" №%1").arg(++iName) :
            groups[i]->getName()
        );
        setTabText(i, tabText);
    }
}

Group* Groups::getGroup() const
{
    return groups[currentIndex()];
}

void Groups::clearActiveGroup()
{
    getGroup()->closeAllSubWindows();
}

void Groups::tileActiveGroup()
{
    getGroup()->tile();
}

void Groups::addPlot()
{
    getGroup()->insertPlot();
}

void Groups::exportActiveGroupToPng()
{    
    if(exportPath.setExistingDirectory(this, tr("Export plots to"))){
        getGroup()->exportToPng(exportPath.getPath());
    }
}

#include <QDir>
void Groups::exportToPng()
{
    if(exportPath.setExistingDirectory(this, tr("Export all groups to"))){
        QDir creator;
        for(int i = 0; i < groups.size(); ++i){
            QString subDir = exportPath.getPath() + "/" + tabText(i);
            if(creator.mkdir(subDir)){
                groups[i]->exportToPng(subDir);
            }
        }
    }
}

void Groups::autoScaleActiveGroup()
{
    getGroup()->autoscale();
}

#include <QAction>
void Groups::setGroupTiling(QAction* action)
{
    getGroup()->setTileType(Group::TileType(action->data().toInt()));
}

void Groups::createGroupChangedSignal(int i)
{
    if(i != -1){
        emit groupChanged(getGroup());
    }
}

#include <QJsonObject>
#include <QJsonArray>
void Groups::serialize(QJsonObject& root, const Path& proPath) const
{
    if(!groups.isEmpty()){
        QJsonArray groupsSettings;
        foreach(Group* group, groups){
            group->serialize(groupsSettings, proPath);
        }
        root.insert("groups", groupsSettings);
    }
}

void Groups::restore(const QJsonObject& root, const Path& proPath)
{
    if(root.contains("groups")){
        foreach(const QJsonValue& group, root.value("groups").toArray()){
            addGroup()->restore(group.toObject(), proPath);
        }
        retitle();
        if(!groups.isEmpty()){
            emit groupChanged(groups.last()); //Чтобы установить активную группу для настроек.
            if(!groups.last()->isEmpty()){
                emit wasActivated(groups.last()->subWindowList().last()); //Чтобы установить активный график для настроек.
            }
        }
    }
}
