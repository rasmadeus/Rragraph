#include "ExportPlotSettings.h"
#include "ui_ExportPlotSettings.h"

ExportPlotSettings::ExportPlotSettings(QWidget *parent) :
    PlotSettings(parent),
    ui(new Ui::ExportPlotSettings)
{
    ui->setupUi(this);
    connect(ui->copy, SIGNAL(clicked()), SIGNAL(dublicateSettings()));
    connect(ui->plotExportHeight, SIGNAL(editingFinished()), SLOT(setExportSize()));
    connect(ui->plotExportWidth, SIGNAL(editingFinished()), SLOT(setExportSize()));
    connect(ui->printPlot, SIGNAL(clicked()), SLOT(printCurrentPlot()));
}

ExportPlotSettings::~ExportPlotSettings()
{
    delete ui;
}

void ExportPlotSettings::retranslate()
{
    ui->retranslateUi(this);
}

#include <Plot.h>
void ExportPlotSettings::copySettingsTo(Plot* plot)
{
    plot->setExportSize(getExportSize());
}

void ExportPlotSettings::fillFromPlot()
{
    QSizeF exportSize = plot->getExportSize();
    ui->plotExportWidth->setValue(exportSize.width());
    ui->plotExportHeight->setValue(exportSize.height());
}

QSizeF ExportPlotSettings::getExportSize() const
{
    return QSizeF(ui->plotExportWidth->value(), ui->plotExportHeight->value());
}

void ExportPlotSettings::setExportSize()
{
    copySettingsTo(plot);
}

#include <QPrinter>
#include <QPrintDialog>
#include <qwt_plot_renderer.h>
#include <QApplication>
void ExportPlotSettings::printCurrentPlot() const
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    printer.setDocName("Plot");
    printer.setCreator(QApplication::applicationVersion());
    printer.setOrientation(QPrinter::Landscape);
    QPrintDialog dialog(&printer, plot);
    if(dialog.exec()){
        QwtPlotRenderer renderer;
        if(printer.colorMode() == QPrinter::GrayScale){
            renderer.setDiscardFlag(QwtPlotRenderer::DiscardBackground);
            renderer.setDiscardFlag(QwtPlotRenderer::DiscardCanvasBackground);
            renderer.setDiscardFlag(QwtPlotRenderer::DiscardCanvasFrame);
            renderer.setLayoutFlag(QwtPlotRenderer::FrameWithScales);
        }
        renderer.renderTo(plot, printer);
    }
}
