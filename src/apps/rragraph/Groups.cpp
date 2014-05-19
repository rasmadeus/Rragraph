#include "Groups.h"

Groups::Groups(QWidget* parent) :
    QTabWidget(parent)
{
    setStyles();
    setLookAndFeel();
    setFocusPolicy(Qt::NoFocus);
    connect(this, SIGNAL(tabCloseRequested(int)), SLOT(tryCloseGroup(int)));
    connect(this, SIGNAL(currentChanged(int)), SLOT(createGroupChangedSignal(int)));
    connect(this, SIGNAL(groupChanged(Group*)), SLOT(emitAboutActiveGroup(Group*)));
}

void Groups::setStyles()
{
    setStyleSheet(
        "QTabBar::tab{"
            "background: qlineargradient("
                "x1: 0, y1: 0, x2: 1, y2: 0,"
                "stop: 0 #ddd,"
                "stop: 0.5 #bbb,"
                "stop: 1.0 #ddd"
            ");"
            "border-bottom-right-radius: 6px;"
            "border-top-right-radius: 6px;"
            "min-height: 15ex;"
            "color: #888;"
            "width: 15px;"
            "padding: 2px;"
            "border: 1px solid #C4C4C3;"                
        "}"

        "QTabBar::tab:selected{"
                "background: qlineargradient("
                    "x1: 0, y1: 0, x2: 1, y2: 0,"
                    "stop: 0 #fff,"
                    "stop: 0.5 #eee,"
                    "stop: 1.0 #fff"
                ");"
                "color: #000;"
        "}"

        "QTabBar::tab:hover{"
            "color: #555;"
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
    addTab(group, "");
    retitle();    
    if(count() == 1){
        emit hasGroups(true);
    }
    setCurrentIndex(count() - 1);
    connect(group, SIGNAL(subWindowActivated(QMdiSubWindow*)), SIGNAL(wasActivated(QMdiSubWindow*)));
    connect(group, SIGNAL(noMorePlots()), SIGNAL(noMorePlots()));
    return group;
}

void Groups::emitAboutActiveGroup(Group* group)
{
    if (group->isEmpty()){
        emit noMorePlots();
    }
}

void Groups::retranslate()
{
    retitle();
    for(int i = 0; i < count(); ++i){
        getGroup(i)->retranslate();
    }
}

void Groups::closeGroup(int i)
{
    Group* group = getGroup(i);
    removeTab(i);
    retitle();
    if(!count()){
        emit hasGroups(false);
        emit noMoreGroup();
    }
    delete group;
}

#include "YesNoMessage.h"
void Groups::tryCloseGroup(int i)
{
    YesNoMessage::proxyAction(
        this,
        true,
        tr("close this tab?"),
        [this, i](){closeGroup(i);}
    );
}

void Groups::closeGroups()
{
    while(count()){
        closeGroup(0);
    }
}

void Groups::retitle()
{
    int iName = 0;
    for(int i = 0; i < count(); ++i){
        Group* group = getGroup(i);
        const QString tabText(
            group->nameIsEmpty()     ?
            tr("Group") +  QString(" №%1").arg(++iName) :
            group->getName()
        );
        setTabText(i, tabText);
    }
}

Group* Groups::getGroup() const
{
    return getGroup(currentIndex());
}

Group* Groups::getGroup(int i) const
{
    return static_cast<Group*>(widget(i));
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

#include <Plot.h>
void Groups::exportActiveGroupToPng()
{    
    if(Plot::exportPath.setExistingDirectory(this, tr("Export plots to"))){
        emit beginExport();
        getGroup()->exportToPng(Plot::exportPath.getPath());
        emit endExport();
    }
}

#include <QDir>
#include <QApplication>
void Groups::exportToPng()
{
    if(Plot::exportPath.setExistingDirectory(this, tr("Export all groups to"))){        
        emit beginExport();
        QApplication::processEvents();
        QDir creator;
        for(int i = 0; i < count(); ++i){            
            QFileInfo subDir(Plot::exportPath.getPath() + "/" + tabText(i));
            if(subDir.exists() || creator.mkdir(subDir.absoluteFilePath())){
                getGroup(i)->exportToPng(subDir.absoluteFilePath());
            }
        }
        emit endExport();
    }
}

void Groups::exportActiveGroupToPdf()
{
    if(Plot::exportPath.setSaveFileName(this, tr("Export to pdf"), tr("Pdf documents") + "(*.pdf);;" + Path::getTemplate(Path::ALL_FILES))){
        emit beginExport();
        getGroup()->exportToPdf(Plot::exportPath.getPath());
        emit endExport();
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
    if(count()){
        QJsonArray groupsSettings;
        for(int i = 0; i < count(); ++i){
            getGroup(i)->serialize(groupsSettings, proPath);
        }
        root.insert("groups", groupsSettings);
    }
}

void Groups::restore(const QJsonObject& root, const Path& proPath)
{
    if(root.contains("groups")){
        QApplication::processEvents();
        foreach(const QJsonValue& group, root.value("groups").toArray()){            
            addGroup()->restore(group.toObject(), proPath);
        }
        retitle();
        activate();
    }
}

void Groups::activate()
{
    if(count()){
        Group* lastGroup = getGroup(count() - 1);
        emit groupChanged(lastGroup); //Чтобы установить активную группу для настроек.
    }
}

Group* Groups::toDefaultState()
{
    closeGroups();
    Group* res = addGroup();
    res->insertPlot();
    return res;
}

void Groups::copySettingsToActiveGroup(PlotSettingsFiller* filler)
{
    getGroup()->copySettings(filler);
}

#include <SamplesManager.h>
void Groups::processArgs(const QStringList& args)
{
    if(!count()){
        toDefaultState();
    }
    getGroup()->getSamplesManager()->append(args);
}

void Groups::setInitialLoadingPath(const QString& path)
{
    for(int i = 0; i < count(); ++i){
        getGroup(i)->setInitialLoadingPath(path);
    }
}
