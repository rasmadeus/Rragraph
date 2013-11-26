#include "MdiArea.h"

SINGLETON_IMPLEMENTATION(MdiArea, QWidget)

MdiArea::MdiArea(QWidget *parent) :
    QMdiArea(parent),
    tileType(GRID_HORIZONTAL)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

#include <QMdiSubWindow>
#include "Plot.h"
#include <QIcon>
Plot* MdiArea::insertPlot()
{
    QMdiSubWindow* window = new QMdiSubWindow;
    window->setMinimumSize(250, 150);
    window->setWindowIcon(QIcon(":/res/addPlot.png"));
    Plot* plot = new Plot(window);
    plot->connect(plot, SIGNAL(destroyed()), this, SLOT(retitle()));
    window->setWidget(plot);
    window->setAttribute(Qt::WA_DeleteOnClose);
    addSubWindow(window);
    window->show();
    retitle();
    return plot;
}

#include <QAction>
void MdiArea::changeTileType(QAction* action)
{
    tileType = TileType(action->data().toInt());
    tile();
}

void MdiArea::retitle()
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

#include "Exporter.h"
#include <QFileDialog>
void MdiArea::exportToPng()
{
    Exporter exporter;
    QString dir = QFileDialog::getExistingDirectory(this, tr("Save to"), exporter.getExportPath());
    if(!dir.isEmpty()){
        foreach(QMdiSubWindow* window, subWindowList()){
            const QString path = dir + "/" + window->windowTitle() + ".png";
            Plot* plot = static_cast<Plot*>(window->widget());
            exporter.renderDocument(plot, path, plot->getExportSize());
        }
        exporter.setExportPath(dir);
    }
}

void MdiArea::autoscale()
{
    foreach(QMdiSubWindow* window, subWindowList()){
        Plot* plot = static_cast<Plot*>(window->widget());
        plot->autoSize();
    }
}

#include <QPrintDialog>
#include <QPrinter>
void MdiArea::print()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setDocName("Plots");
    printer.setCreator("Rragraph 4.0");
    printer.setOrientation(QPrinter::Landscape);

    Exporter exporter;
    QPrintDialog dialog(&printer, this);
    if(dialog.exec()){
        if(printer.colorMode() == QPrinter::GrayScale){
            exporter.setDiscardFlag(QwtPlotRenderer::DiscardBackground);
            exporter.setDiscardFlag(QwtPlotRenderer::DiscardCanvasBackground);
            exporter.setDiscardFlag(QwtPlotRenderer::DiscardCanvasFrame);
            exporter.setLayoutFlag(QwtPlotRenderer::FrameWithScales);
        }
        bool needNewPage = false;
        foreach(QMdiSubWindow* window, subWindowList()){
            if(needNewPage){
                printer.newPage();
            }
            else{
                needNewPage = true;
            }
            Plot* plot = static_cast<Plot*>(window->widget());
            exporter.renderTo(plot, printer);
        }
    }
}

#include <QJsonArray>
#include <QJsonObject>
void MdiArea::serialize(QJsonObject& root) const
{
    QJsonArray plots;   
    foreach(QMdiSubWindow* window, subWindowList()){
        Plot* plot = static_cast<Plot*>(window->widget());
        plot->serialize(plots);
    }
    root["plots"] = plots;
    root["tileType"] = int(tileType);
}

void MdiArea::restore(const QJsonObject& root)
{
    tileType = TileType(root.value("tileType").toVariant().toInt());
    foreach(const QJsonValue& value, root.value("plots").toArray()) {
        insertPlot()->restore(value);
    }
    if(subWindowList().size()){
        QMdiSubWindow* activeWindow = subWindowList().at(subWindowList().size() - 1);
        setActiveSubWindow(activeWindow);
        emit subWindowActivated(activeWindow);
    }
}

void MdiArea::serializeCurves(QJsonObject& root) const
{
    QJsonArray plots;
    foreach(QMdiSubWindow* window, subWindowList()){
        Plot* plot = static_cast<Plot*>(window->widget());
        plot->serializeCurves(plots);
    }
    root["plotsCurves"] = plots;
}

void MdiArea::restoreCurves(int iFile, const QJsonObject& root)
{
    QJsonArray curves = root.value("plotsCurves").toArray();
    int iPlot = 0;
    foreach(QMdiSubWindow* window, subWindowList()){
        Plot* plot = static_cast<Plot*>(window->widget());
        plot->restoreCurves(iFile, curves.at(iPlot).toArray().at(iFile).toObject());
        ++iPlot;
    }
}

#include "CurveSettingsView.h"
void MdiArea::localeWasChanged()
{
    CurveSettingsView::getInstance()->localeWasChanged();
    foreach(QMdiSubWindow* window, subWindowList()){
        window->setWindowTitle(
            tr("Plot №%1").arg(
                subWindowList().indexOf(window) + 1
            )
        );
    }
}
