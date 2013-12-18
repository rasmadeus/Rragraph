#ifndef AXES_H
#define AXES_H

class AxisPlotSettings;
#include "PlotSettings.h"

namespace Ui {
class Axes;
}

class Axes : public PlotSettings
{
    Q_OBJECT

public:
    explicit Axes(QWidget *parent = 0);
    ~Axes();
    void localeWasChanged();
protected slots:
    void setNativeValues();
    void setPlot(Plot* owner);
protected:
    void dublicateValues(Plot* plot);
private:
    AxisPlotSettings* x;
    AxisPlotSettings* y;
    Ui::Axes *ui;
};

#endif // AXES_H



