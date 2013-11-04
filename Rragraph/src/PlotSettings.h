#ifndef PLOTSETTINGS_H
#define PLOTSETTINGS_H

class Plot;
#include <QWidget>

class PlotSettings : public QWidget
{
    Q_OBJECT
public:
    explicit PlotSettings(QWidget *parent = 0);
    void setOwner(Plot* owner);
protected slots:    
    virtual void setNativeValues() = 0;
    void dublicateValues();
protected:
    virtual void setPlot(Plot* owner);
    virtual void dublicateValues(Plot* plot) = 0;
    Plot* owner;
};

#endif // PLOTSETTINGS_H
