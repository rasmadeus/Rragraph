#include "ExportSettings.h"
#include "ui_ExportSettings.h"

ExportSettings::ExportSettings(QWidget *parent) :
    PlotSettings(parent),
    ui(new Ui::ExportSettings)
{
    ui->setupUi(this);
    connect(ui->dublicate, SIGNAL(clicked()),            SLOT(dublicateValues()));
    connect(ui->width,     SIGNAL(valueChanged(double)), SLOT(setExportSize()));
    connect(ui->height,    SIGNAL(valueChanged(double)), SLOT(setExportSize()));
    connect(ui->exportTo,  SIGNAL(clicked()),            SLOT(exportPlot()));
    connect(ui->print,     SIGNAL(clicked()),            SLOT(printPlot()));
}

ExportSettings::~ExportSettings()
{
    delete ui;
}

#include "Plot.h"
void ExportSettings::setNativeValues()
{
    const QSizeF exportSize = owner->getExportSize();
    ui->width->setValue(exportSize.width());
    ui->height->setValue(exportSize.height());
}

void ExportSettings::dublicateValues(Plot* plot){
    plot->setExportSize(QSizeF(ui->width->value(), ui->height->value()));
}

void ExportSettings::localeWasChanged(){
    ui->retranslateUi(this);
}

void ExportSettings::setExportSize()
{
    if(owner){
        dublicateValues(owner);
    }    
}

#include "Exporter.h"
void ExportSettings::exportPlot()
{
    if(owner){
        Exporter().exportOne(owner);
    }
}

void ExportSettings::printPlot()
{
    if(owner){
        Exporter().printOne(owner);
    }    
}
