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

void ExportPlotSettings::printCurrentPlot() const
{

}
