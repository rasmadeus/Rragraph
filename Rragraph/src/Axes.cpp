#include "Axes.h"
#include "ui_Axes.h"

#include "AxisPlotSettings.h"
Axes::Axes(QWidget *parent) :
    PlotSettings(parent),
    ui(new Ui::Axes)
{
    ui->setupUi(this);

    x = new AxisPlotSettings(QwtPlot::xBottom, this);
    y = new AxisPlotSettings(QwtPlot::yLeft, this);
    ui->x->layout()->addWidget(x);
    ui->y->layout()->addWidget(y);
}

Axes::~Axes()
{
    delete ui;
}

void Axes::setPlot(Plot* owner)
{
    x->setPlot(owner);
    y->setPlot(owner);
}

void Axes::localeWasChanged()
{
    x->localeWasChanged();
    y->localeWasChanged();
    ui->retranslateUi(this);
}

void Axes::setNativeValues()
{
    x->setNativeValues();
    y->setNativeValues();
}

void Axes::dublicateValues(Plot* plot)
{
    x->dublicateValues(plot);
    y->dublicateValues(plot);
}
