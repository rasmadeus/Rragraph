#include "Group.h"

#include <SamplesManager.h>
#include <CurvesManagerView.h>
Group::Group(QWidget* parent) :
    QMdiArea(parent),
    tileType(GRID_HORIZONTAL)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    samplesManager = new SamplesManager();
    curvesManagerView = new CurvesManagerView(samplesManager, this);
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
    PlotWithCurves* plot = new PlotWithCurves(samplesManager, curvesManagerView, window);
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

const QString& Group::getName() const
{
    return name;
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

void Group::forEachPlotDo(const std::function<void (QMdiSubWindow*, PlotWithCurves*)>& action)
{
    foreach(QMdiSubWindow* window, subWindowList()){
        action(window, static_cast<PlotWithCurves*>(window->widget()));
    }
}

void Group::autoscale()
{
    forEachPlotDo([](QMdiSubWindow*, PlotWithCurves* plot){plot->autoscale();});
}

SamplesManager* Group::getSamplesManager() const
{
    return samplesManager;
}

#include <qwt_plot_renderer.h>
void Group::exportToPng(const QString& dir)
{
    QwtPlotRenderer exporter;
    forEachPlotDo(
        [&](QMdiSubWindow* window, PlotWithCurves* plot){
            QString plotTitle = window->windowTitle();
            QString fileName = dir + "/" + plotTitle + ".png";
            exporter.renderDocument(plot, fileName, plot->getExportSize());
        }
    );
}

bool Group::isEmpty() const
{
    return subWindowList().isEmpty();
}

#include "PlotSettings.h"
void Group::dublicateSettings(PlotSettings* plotSettings)
{
    forEachPlotDo(
        [&](QMdiSubWindow* window, PlotWithCurves* plot){
            Q_UNUSED(window)
            plotSettings->copySettingsTo(plot);
        }
    );
}
