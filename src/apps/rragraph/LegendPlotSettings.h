#ifndef LEGENDPLOTSETTINGS_H
#define LEGENDPLOTSETTINGS_H

#include "PlotSettings.h"

namespace Ui {
class LegendPlotSettings;
}

class LegendPlotSettings : public PlotSettings
{
    Q_OBJECT

public:
    explicit LegendPlotSettings(QWidget *parent = 0);
    ~LegendPlotSettings();
    void copySettingsTo(Plot* plot);
protected:
    void fillFromPlot();
private slots:
    void turnLegend(bool on);
    void setFont();
    void setOpacity(int opacity);
    void setMaximumColumns(int count);
    void setPos();
private:
    void updatePos(Plot* plot);
    void fillPos();
    Ui::LegendPlotSettings *ui;
};

#endif // LEGENDPLOTSETTINGS_H
