#include "AxisPlotSettings.h"
#include "ui_AxisPlotSettings.h"

#include "Plot.h"
AxisPlotSettings::AxisPlotSettings(QwtPlot::Axis axis, QWidget *parent) :
    PlotSettings(parent),
    ui(new Ui::AxisPlotSettings),
    axis(axis),
    lockUpdatingOwner(false)
{

    ui->setupUi(this);

    connect(ui->min,       SIGNAL(valueChanged(double)), SLOT(updateOwnerScale()));
    connect(ui->max,       SIGNAL(valueChanged(double)), SLOT(updateOwnerScale()));
    connect(ui->step,      SIGNAL(valueChanged(double)), SLOT(updateOwnerScale()));
    connect(ui->title,     SIGNAL(textEdited(QString)),  SLOT(updateAxisTitle(QString)));
    connect(ui->dublicate, SIGNAL(clicked()),            SLOT(dublicateValues()));   

}

void AxisPlotSettings::loseTitleFocus()
{
    ui->title->deselect();
}

AxisPlotSettings::~AxisPlotSettings(){
    delete ui;
}

void AxisPlotSettings::localeWasChanged(){
    ui->retranslateUi(this);
}

void AxisPlotSettings::updateAxisTitle(const QString &title){
    if(owner){
        owner->setAxisTitle(axis, title);
    }
}

#include <qwt_interval.h>
void AxisPlotSettings::setPlot(Plot* plot)
{
    if(owner){
        disconnect(owner, SIGNAL(zoomed()), this, SLOT(setNativeValues()));
    }
    if(plot){
        connect(plot, SIGNAL(zoomed()), SLOT(setNativeValues()));
    }
    owner = plot;
}
#include "MdiArea.h"
void AxisPlotSettings::updateOwnerScale()
{
    if(!lockUpdatingOwner && owner){
        updateAxiScale(owner);
    }
}

#include <qwt_scale_div.h>
void AxisPlotSettings::setNativeValues()
{
    const QwtInterval interval = owner->axisInterval(axis);
    lockUpdatingOwner = true;
        ui->step->setValue(owner->axiStep(axis)); //It must be invoked before others
        ui->min->setValue(interval.minValue());
        ui->max->setValue(interval.maxValue());
        ui->title->setText(owner->axisTitle(axis).text());
    lockUpdatingOwner = false;
}

void AxisPlotSettings::updateAxiScale(Plot* plot)
{
    plot->setAxisScale(
        axis,
        ui->min->value(),
        ui->max->value(),
        ui->step->value()
    );
    plot->replot();    
}

void AxisPlotSettings::dublicateValues(Plot* plot)
{
    updateAxiScale(plot);
    plot->setAxisTitle(axis, ui->title->text());    
}
