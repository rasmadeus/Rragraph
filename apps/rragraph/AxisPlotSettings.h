#ifndef AXISPLOTSETTINGS_H
#define AXISPLOTSETTINGS_H


#include <qwt_plot.h>
#include "PlotSettings.h"

namespace Ui {
class AxisPlotSettings;
}

class AxisPlotSettings : public PlotSettings
{
    Q_OBJECT
public:
    explicit AxisPlotSettings(QwtPlot::Axis axis, QWidget* parent = 0);
    ~AxisPlotSettings();
    void localeWasChanged();
    void dublicateValues(Plot* plot);
public slots:
    void setNativeValues();
    void setPlot(Plot* owner);
private slots:
    void updateOwnerScale();
    void updateAxisTitle(const QString& title);
private:
    void updateAxiScale(Plot* plot);
    Ui::AxisPlotSettings* ui;
    QwtPlot::Axis axis;
    bool lockUpdatingOwner;
};

#endif // AXISPLOTSETTINGS_H
