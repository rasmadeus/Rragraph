#ifndef AXISPLOTSETTINGS_H
#define AXISPLOTSETTINGS_H

#include <qwt_plot.h>
#include "FontColorSettingsAble.h"

namespace Ui {
class AxisPlotSettings;
}

class AxisPlotSettings : public FontColorSettingsAble
{
    Q_OBJECT
public:
    explicit AxisPlotSettings(QwtPlot::Axis axis, QWidget* parent = 0);
    ~AxisPlotSettings();
    void copySettingsTo(Plot* plot);
protected:
    void fillFromPlot();
    void setPlot(Plot* plot);
    QwtText getText() const;
    void setText(const QwtText& text);
private slots:
    void updateScale();
    void setAxisTitle();
    void fillScale();
private:
    void updateScale(QwtPlot* plot);
    Ui::AxisPlotSettings *ui;
    QwtPlot::Axis axis;
};

#endif // AXISPLOTSETTINGS_H
