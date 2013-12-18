#ifndef LEGENDSETTINGS_H
#define LEGENDSETTINGS_H

#include "PlotSettings.h"

namespace Ui {
class LegendSettings;
}

class LegendSettings : public PlotSettings
{
    Q_OBJECT
public:
    explicit LegendSettings(QWidget *parent = 0);
    ~LegendSettings();
    void localeWasChanged();
protected slots:
    void setNativeValues();
private slots:
    void setFont();
    void alignmentChanged();
    void setOpacity(int opacity);
    void turnLegend(bool on);
    void setMaximumColumns(int count);
protected:
    void dublicateValues(Plot* plot);
private:
    void setAlignment(Plot* plot);
    void setOpacity(Plot* plot, int opacity);
    Ui::LegendSettings* ui;
};

#endif // LEGENDSETTINGS_H
