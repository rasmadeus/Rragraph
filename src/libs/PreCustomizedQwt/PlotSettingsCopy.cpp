#include "PlotSettings.h"

PlotSettingsFiller::~PlotSettingsFiller()
{
}

PlotSettingsFiller::PlotSettingsFiller(Plot* donor):
    donor(donor)
{
}

class PassFiller: public PlotSettingsFiller
{
public:
    PassFiller(Plot* donor):
        PlotSettingsFiller(donor)
    {
    }

    void fill(Plot* plot)
    {
        Q_UNUSED(plot)
    }
};

#include "Plot.h"
class PlotTitleFiller: public PlotSettingsFiller
{
public:
    PlotTitleFiller(Plot* donor):
        PlotSettingsFiller(donor)
    {
    }

    void fill(Plot* plot)
    {
        plot->setTitle(donor->title());
    }
};

class AxisFiller: public PlotSettingsFiller
{
    int axis;
public:
    AxisFiller(Plot* donor, int axis):
        PlotSettingsFiller(donor),
        axis(axis)
    {
    }

    void fill(Plot* plot)
    {
        plot->setAxisTitle(axis, donor->axisTitle(axis));
        const QwtInterval interval = donor->axisInterval(axis);
        plot->setAxisScale(axis, interval.minValue(), interval.maxValue(), donor->axisStep(QwtPlot::Axis(axis)));
        plot->replot();
    }
};

#include "LegendItem.h"
class LegendFiller: public PlotSettingsFiller
{
public:
    LegendFiller(Plot* donor):
        PlotSettingsFiller(donor)
    {
    }

    void fill(Plot* plot)
    {
        LegendItem* legend = plot->getLegend();
        LegendItem* donorLegend = donor->getLegend();
        legend->setVisible(donorLegend->isVisible());
        legend->setFont(donorLegend->font());
        legend->setMaxColumns(donorLegend->maxColumns());
        legend->setBackgroundOpacity(donorLegend->backgroundBrush().color().alpha());
        legend->setAlignment(donorLegend->alignment());
        plot->replot();
    }
};

class ExportFiller: public PlotSettingsFiller
{
public:
    ExportFiller(Plot* donor):
        PlotSettingsFiller(donor)
    {
    }

    void fill(Plot* plot)
    {
        plot->setExportSize(donor->getExportSize());
        plot->setResolution(donor->getResolution());
    }
};

PlotSettingsFiller* PlotSettingsFiller::make(SettingsType type, Plot* donor)
{
    switch(type){
        case PLOT_TITLE_SETTINGS: return new PlotTitleFiller(donor);
        case ABSCISS_SETTINGS:    return new AxisFiller(donor, QwtPlot::xBottom);
        case ORDINATE_SETTINGS:   return new AxisFiller(donor, QwtPlot::yLeft);
        case LEGEND_SETTINGS:     return new LegendFiller(donor);
        case EXPORT_SETTINGS:     return new ExportFiller(donor);
        default:                  return new PassFiller(donor);
    }
}

void PlotSettings::copyPlotTitle()
{
    emit copySettings(PlotSettingsFiller::make(PlotSettingsFiller::PLOT_TITLE_SETTINGS, plot));
}

void PlotSettings::copyX()
{
    emit copySettings(PlotSettingsFiller::make(PlotSettingsFiller::ABSCISS_SETTINGS, plot));
}

void PlotSettings::copyY()
{
    emit copySettings(PlotSettingsFiller::make(PlotSettingsFiller::ORDINATE_SETTINGS, plot));
}

void PlotSettings::copyLegend()
{
    emit copySettings(PlotSettingsFiller::make(PlotSettingsFiller::LEGEND_SETTINGS, plot));
}

void PlotSettings::copyExport()
{
    emit copySettings(PlotSettingsFiller::make(PlotSettingsFiller::EXPORT_SETTINGS, plot));
}
