#include "PlotsGroups.h"

PlotsGroups::PlotsGroups(QWidget* parent) :
    QTabWidget(parent)
{
    setStyles();
    setLookAndFeel();
    setFocusPolicy(Qt::NoFocus);
    connect(this, SIGNAL(tabCloseRequested(int)), SLOT(closeGroup(int)));
    connect(this, SIGNAL(currentChanged(int)), SLOT(createGroupChangedSignal(int)));
}

void PlotsGroups::setStyles()
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

void PlotsGroups::setLookAndFeel()
{
    setTabsClosable(true);
    setMovable(true);
    setUsesScrollButtons(true);
    setTabPosition(East);
}

#include "Group.h"
void PlotsGroups::addPlots()
{
    Group* plots = new Group(this);
    groups << plots;
    addTab(plots, "");
    retitle();    
    if(count() == 1){
        emit hasGroups(true);
    }
    setCurrentIndex(count() - 1);
}

void PlotsGroups::closeGroup(int i)
{
    removeTab(i);
    delete groups.takeAt(i);
    retitle();
    if(groups.isEmpty()){
        emit hasGroups(false);
    }
}

void PlotsGroups::closeGroups()
{
    while(!groups.isEmpty()){
        closeGroup(0);
    }
}

void PlotsGroups::retitle()
{
    int iName = 0;
    for(int i = 0; i < count(); ++i){
        if(groups[i]->nameIsEmpty()){
            setTabText(i, tr("Group №%1").arg(++iName));
        }
    }
}

Group* PlotsGroups::getGroup() const
{
    return groups[currentIndex()];
}

void PlotsGroups::clearActiveGroup()
{
    getGroup()->closeAllSubWindows();
}

void PlotsGroups::tileActiveGroup()
{
    getGroup()->tile();
}

void PlotsGroups::addPlot()
{
    getGroup()->insertPlot();
}

void PlotsGroups::exportActiveGroup()
{

}

void PlotsGroups::autoScaleActiveGroup()
{
    getGroup()->autoscale();
}

#include <QAction>
void PlotsGroups::setGroupTiling(QAction* action)
{
    getGroup()->setTileType(Group::TileType(action->data().toInt()));
}

void PlotsGroups::createGroupChangedSignal(int i)
{
    if(i != -1){
        emit groupChanged(getGroup());
    }
}
