#ifndef EXPORTSETTINGS_H
#define EXPORTSETTINGS_H

#include "PlotSettings.h"

namespace Ui {
class ExportSettings;
}

class ExportSettings : public PlotSettings
{
    Q_OBJECT    
public:
    explicit ExportSettings(QWidget *parent = 0);
    ~ExportSettings();
    void localeWasChanged();
protected slots:
    void setNativeValues();
protected:
    void dublicateValues(Plot* plot);
private slots:
    void setExportSize();
    void exportPlot();
    void printPlot();
private:
    Ui::ExportSettings* ui;
};

#endif // EXPORTSETTINGS_H
