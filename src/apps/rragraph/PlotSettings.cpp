#include "PlotSettings.h"

PlotSettings::PlotSettings(QWidget *parent) :
    QWidget(parent),
    plot(nullptr)
{
    connect(this, SIGNAL(dublicateSettings()), SLOT(makeCopySignal()));
    setEnabled(false);
}

void PlotSettings::setEasyMark(Plot* plot)
{
    setPlot(plot);
    fillFromPlot();
    setEnabled(true);
}

void PlotSettings::toDefaultState()
{
    plot = nullptr;
    setEnabled(false);
}

void PlotSettings::setPlot(Plot* plot)
{
    this->plot = plot;
}

void PlotSettings::makeCopySignal()
{
    emit copyFrom(this);
}
