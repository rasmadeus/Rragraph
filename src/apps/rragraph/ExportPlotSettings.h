#ifndef EXPORTPLOTSETTINGS_H
#define EXPORTPLOTSETTINGS_H

#include "PlotSettings.h"

namespace Ui {
class ExportPlotSettings;
}

class ExportPlotSettings : public PlotSettings
{
    Q_OBJECT

public:
    explicit ExportPlotSettings(QWidget *parent = 0);
    ~ExportPlotSettings();
    void copySettingsTo(Plot* plot);
protected:
    void fillFromPlot();
protected slots:
    void setExportSize();
    void printCurrentPlot() const;
private:
    QSizeF getExportSize() const;
    Ui::ExportPlotSettings *ui;
};

#endif // EXPORTPLOTSETTINGS_H
