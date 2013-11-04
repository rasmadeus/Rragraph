#include "MdiArea.h"

MdiArea* MdiArea::instance = nullptr;

void MdiArea::create(QWidget* parent)
{
    if(!instance){
        instance = new MdiArea(parent);
    }
}

MdiArea* MdiArea::getInstance(){
    return instance;
}

MdiArea::MdiArea(QWidget *parent) :
    QMdiArea(parent)
{

}

#include <QMdiSubWindow>
#include "Plot.h"
#include <QIcon>
Plot* MdiArea::insertPlot()
{
    QMdiSubWindow* window = new QMdiSubWindow(this);
    Plot* plot = new Plot(window);
    window->setWidget(plot);
    window->setAttribute(Qt::WA_DeleteOnClose);
    plot->connect(plot, SIGNAL(destroyed()), this, SLOT(retitle()));
    window->show();
    window->setWindowIcon(QIcon(":/res/addPlot.png"));
    retitle();
    return plot;
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
        tileSubWindows();
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
#include <QJsonValue>
QJsonObject MdiArea::serialize() const
{
    QJsonArray plots;
    foreach(QMdiSubWindow* window, subWindowList()){
        Plot* plot = static_cast<Plot*>(window->widget());
        plots.push_back(plot->serialize());
    }
    QJsonObject obj;
    obj["plots"] = plots;
    return obj;
}

void MdiArea::restore(const QJsonObject& obj)
{
    foreach(const QJsonValue& item, obj.value("plots").toArray()){
        Plot* plot = insertPlot();
        plot->restore(item.toObject());
    }
    if(subWindowList().size() > 0){
        setActiveSubWindow(subWindowList().at(0));
    }
}
