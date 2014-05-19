#include "Group.h"

#include <SamplesManager.h>
#include <CurvesManagerView.h>
Group::Group(QWidget* parent) :
    QMdiArea(parent),
    tileType(GRID_STRAIGHT)
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

void Group::retranslate()
{
    retitle();
    curvesManagerView->retranslate();
}

#include <QMdiSubWindow>
#include "PlotWithCurves.h"
PlotWithCurves* Group::insertPlot()
{
    QMdiSubWindow* window = new QMdiSubWindow;
    {
        window->setMinimumSize(250, 150);
        window->setWindowIcon(QIcon(":/res/mainWindow/closeAllPlots.png"));
        window->setAttribute(Qt::WA_DeleteOnClose);
    }
    PlotWithCurves* plot = new PlotWithCurves(samplesManager, curvesManagerView, window);
    {
        plot->connect(plot, SIGNAL(destroyed()), this, SLOT(retitle()));
        window->setWidget(plot);
        addSubWindow(window);
        window->show();
        retitle();
    }
    return plot;
}

void Group::retitle()
{
    if(subWindowList().isEmpty()){
        emit noMorePlots();
    }
    else{
        foreach(QMdiSubWindow* window, subWindowList()){
            window->setWindowTitle(
                tr("Plot ") +  QString("№%1").arg(
                    subWindowList().indexOf(window) + 1
                )
            );
        }
        if(!subWindowList().isEmpty()){
            tile();
        }
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

void Group::forEachPlotDo(const std::function<void (QMdiSubWindow*, PlotWithCurves*)>& action) const
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
            plot->exportToPng(exporter, fileName);
        }
    );
}


#include <Plot.h>
#include <QPainter>
static void renderWindowTo(QMdiSubWindow* window, QPainter* painter, const QRectF& rect, QwtPlotRenderer& renderer)
{
    renderer.render(
        static_cast<QwtPlot*>(window->widget()),
        painter,
        rect
    );
}

#include <QPrinter>
void Group::exportToPdf(const QString& fileName)
{
    QPrinter printer;
    {
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setPageMargins(20, 30, 20, 10, QPrinter::Millimeter);
        printer.setOrientation(QPrinter::Landscape);
        printer.setOutputFileName(fileName);
    }
    QRectF rect(0, 0, printer.width(), printer.height());
    {
        double aspect = rect.width() / rect.height();
        if (( aspect < 1.0)){
            rect.setHeight(aspect * rect.width());
        }
    }
    {
        QwtPlotRenderer renderer;
        QPainter painter(&printer);
        QList<QMdiSubWindow*> visibleWindows = this->visibleWindows();
        if(!visibleWindows.isEmpty()){
            {
                renderWindowTo(visibleWindows.first(), &painter, rect, renderer);
                visibleWindows.takeFirst();
            }
            {
                foreach(QMdiSubWindow* window, visibleWindows){
                    if(printer.newPage()){
                        renderWindowTo(window, &painter, rect, renderer);
                    }
                }
            }
        }
    }
}

bool Group::isEmpty() const
{
    return subWindowList().isEmpty();
}

#include <QJsonArray>
#include <QJsonObject>
void serializeExistString(const QString& name, QJsonObject& groupSettings)
{
    if(!name.isEmpty()){
        groupSettings.insert("name", name);
    }
}

void restoreExistString(QString& name, const QJsonObject& groupSettings)
{
    if(groupSettings.contains("name")){
        name = groupSettings.value("name").toString();
    }
}

void Group::serialize(QJsonArray& groupsSettings, const Path& proPath) const
{
    QJsonObject groupSettings;
        groupSettings.insert("tileType", QJsonValue::fromVariant(tileType));
        serializeExistString(name, groupSettings);
        serializePlots(groupSettings);
        samplesManager->serialize(groupSettings, proPath);
    groupsSettings.append(groupSettings);
}

void Group::restore(const QJsonObject& groupSettings, const Path& proPath)
{
    tileType = TileType(groupSettings.value("tileType").toVariant().toInt());
    restoreExistString(name, groupSettings);
    restorePlots(groupSettings);
    samplesManager->restore(groupSettings, proPath);
}

void Group::serializePlots(QJsonObject& groupSettings) const
{
    if(!isEmpty()){
        QJsonArray plots;
        forEachPlotDo(
            [&](QMdiSubWindow* window, PlotWithCurves* plot){
                Q_UNUSED(window)
                plot->serialize(plots);
            }
        );
        groupSettings.insert("group", plots);
    }
}

void Group::restorePlots(const QJsonObject& groupSettings)
{
    if(groupSettings.contains("group")){
        foreach(const QJsonValue& group, groupSettings.value("group").toArray()){
            insertPlot()->restore(group.toObject());
        }
    }
}

#include <PlotSettings.h>
void Group::copySettings(PlotSettingsFiller* filler)
{
    forEachPlotDo(
        [&](QMdiSubWindow* window, PlotWithCurves* plot){
            Q_UNUSED(window)
            filler->fill(plot);
        }
    );
}

void Group::setInitialLoadingPath(const QString& path)
{
    curvesManagerView->setInitialLoadingPath(path);
}
