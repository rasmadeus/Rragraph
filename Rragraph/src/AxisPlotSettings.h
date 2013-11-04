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
    Ui::AxisPlotSettings* ui;
    QwtPlot::Axis axis;
public:
    explicit AxisPlotSettings(QwtPlot::Axis axis, QWidget* parent = 0);
    ~AxisPlotSettings();
protected slots:
    void setNativeValues();
    void setPlot(Plot* owner);
private slots:
    void updateOwnerScale();
    void updateAxisTitle(const QString& title);
protected:
    void dublicateValues(Plot* plot);
private:
    void updateAxiScale(Plot* plot);
};

#endif // AXISPLOTSETTINGS_H
