#include "AxisPlotSettings.h"
#include "ui_AxisPlotSettings.h"

AxisPlotSettings::AxisPlotSettings(QwtPlot::Axis axis, QWidget *parent) :
    FontColorSettingsAble(parent),
    ui(new Ui::AxisPlotSettings),
    axis(axis)
{
    ui->setupUi(this);
    ui->axisGroup->setTitle(tr(axis == QwtPlot::xBottom ? "Absciss settings" : "Ordinate settings"));
    connect(ui->min, SIGNAL(valueChanged(double)), SLOT(updateScale()));
    connect(ui->max, SIGNAL(valueChanged(double)), SLOT(updateScale()));
    connect(ui->step, SIGNAL(valueChanged(double)), SLOT(updateScale()));
    connect(ui->title, SIGNAL(textChanged(QString)), SLOT(setAxisTitle()));
    connect(ui->color, SIGNAL(clicked()), SLOT(setColor()));
    connect(ui->font, SIGNAL(clicked()), SLOT(setFont()));
    connect(ui->copy, SIGNAL(clicked()), SIGNAL(dublicateSettings()));
}

AxisPlotSettings::~AxisPlotSettings()
{
    delete ui;
}

void AxisPlotSettings::retranslate()
{
    ui->retranslateUi(this);
}

#include "PlotWithCurves.h"
void AxisPlotSettings::fillFromPlot()
{
    fillScale();
    ui->title->setText(plot->axisTitle(axis).text());
}

void AxisPlotSettings::fillScale()
{
    QwtInterval axisInterval = plot->axisInterval(axis);
    ui->step->setValue(plot->axisStep(axis));
    ui->min->setValue(axisInterval.minValue());
    ui->max->setValue(axisInterval.maxValue());
}

void AxisPlotSettings::updateScale()
{
    updateScale(plot);
}

void AxisPlotSettings::setAxisTitle()
{
    QwtText title = plot->axisTitle(axis);
    title.setText(ui->title->text());
    plot->setAxisTitle(axis, title);
}

void AxisPlotSettings::updateScale(QwtPlot* plot)
{
    plot->setAxisScale(axis, ui->min->value(), ui->max->value(), ui->step->value());
    plot->replot();
}

void AxisPlotSettings::copySettingsTo(Plot* plot)
{
    updateScale(plot);
    plot->setAxisTitle(axis, this->plot->axisTitle(axis));
}

void AxisPlotSettings::setPlot(Plot* plot)
{
    if(this->plot){
        disconnect(this->plot, SIGNAL(zoomed()), this, SLOT(fillScale()));
    }
    connect(plot, SIGNAL(zoomed()), SLOT(fillScale()));
    PlotSettings::setPlot(plot);
}

QwtText AxisPlotSettings::getText() const
{
    return plot->axisTitle(axis);
}

void AxisPlotSettings::setText(const QwtText& text)
{
    plot->setAxisTitle(axis, text);
}
