#ifndef COMMONPLOTSETTINGS_H
#define COMMONPLOTSETTINGS_H

#include "PlotSettings.h"

namespace Ui {
class CommonPlotSettings;
}

class CommonPlotSettings : public PlotSettings
{
    Q_OBJECT

public:
    explicit CommonPlotSettings(QWidget *parent = 0);
    ~CommonPlotSettings();
    void localeWasChanged();
    void dublicateValues(Plot* plot);
public slots:
    void setNativeValues();
private slots:
    void setTitle(const QString& title);
    void setTitleFont();
    void setTitleColor();
private:
    Ui::CommonPlotSettings *ui;
};

#endif // COMMONPLOTSETTINGS_H
