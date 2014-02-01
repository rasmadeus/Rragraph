#include "Group.h"

#include <SamplesManager.h>
#include "CurvesCustomizer.h"
Group::Group(QWidget* parent) :
    QMdiArea(parent),
    tileType(GRID_HORIZONTAL)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    samplesManager = new SamplesManager();
    curvesCustomizer = new CurvesCustomizer(samplesManager, this);
}

Group::~Group()
{
    delete samplesManager;
}

#include <QMdiSubWindow>
#include "PlotWithCurves.h"
PlotWithCurves* Group::insertPlot()
{
    QMdiSubWindow* window = new QMdiSubWindow;
    window->setMinimumSize(250, 150);
    window->setWindowIcon(QIcon(":/res/mainWindow/plot.png"));
    PlotWithCurves* plot = new PlotWithCurves(samplesManager, curvesCustomizer, window);
    plot->connect(plot, SIGNAL(destroyed()), this, SLOT(retitle()));
    window->setWidget(plot);
    window->setAttribute(Qt::WA_DeleteOnClose);
    addSubWindow(window);
    window->show();
    retitle();
    return plot;
}

void Group::retitle()
{
    foreach(QMdiSubWindow* window, subWindowList()){
        window->setWindowTitle(
            tr("Plot №%1").arg(
                subWindowList().indexOf(window) + 1
            )
        );
    }
    if(!subWindowList().isEmpty()){
        tile();
    }
}

QList<QMdiSubWindow*> Group::visibleWindows()
{
    QList<QMdiSubWindow*> windows;
    foreach(QMdiSubWindow* window, subWindowList()){
        if(!window->isMinimized()){
            if(window->isMaximized()){
                window->showNormal();
            }
            windows.push_back(window);
        }
    }
    return windows;
}

void Group::setName(const QString& name)
{
    this->name = name;
}

bool Group::nameIsEmpty() const
{
    return name.isEmpty();
}

void Group::setTileType(TileType tileType)
{
    this->tileType = tileType;
    tile();
}

Group::TileType Group::getTileType() const
{
    return tileType;
}

void Group::forEachPlotDo(const std::function<void (PlotWithCurves *)>& action)
{
    foreach(QMdiSubWindow* window, subWindowList()){
        action(static_cast<PlotWithCurves*>(window->widget()));
    }
}

void Group::autoscale()
{
    forEachPlotDo([](PlotWithCurves* plot){plot->autoscale();});
}

SamplesManager* Group::getSamplesManager() const
{
    return samplesManager;
}
