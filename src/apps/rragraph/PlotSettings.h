#ifndef PLOTSETTINGS_H
#define PLOTSETTINGS_H

class Plot;
#include <QWidget>

class PlotSettings : public QWidget
{
    Q_OBJECT
public:
    explicit PlotSettings(QWidget *parent = 0);
    void setEasyMark(Plot* plot);
    virtual void toDefaultState();
    virtual void copySettingsTo(Plot* plot) = 0;
    virtual void retranslate() = 0;
signals:
    void dublicateSettings();
    void copyFrom(PlotSettings* plotSettings);
    void catchPlot();
    void freePlot();
private slots:
    void makeCopySignal();
protected:
    virtual void fillFromPlot() = 0;
    virtual void setPlot(Plot* plot);
    Plot* plot;
};

#endif // PLOTSETTINGS_H
