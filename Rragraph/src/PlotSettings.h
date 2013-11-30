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
    virtual void localeWasChanged() = 0;
    virtual void dublicateValues(Plot* plot) = 0;
    virtual void setPlot(Plot* owner);
public slots:
    virtual void setNativeValues() = 0;
protected slots:    
    void dublicateValues();
protected:
    Plot* owner;
};

#endif // PLOTSETTINGS_H
