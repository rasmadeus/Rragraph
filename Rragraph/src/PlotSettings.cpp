#include "PlotSettings.h"

PlotSettings::PlotSettings(QWidget *parent) :
    QWidget(parent),
    owner(nullptr)
{
    setEnabled(false);
}

void PlotSettings::setPlot(Plot* owner){
    this->owner = owner;
}

void PlotSettings::setOwner(Plot* owner)
{
    setPlot(owner);
    if(owner){
        setNativeValues();        
    }
    setEnabled(owner);
}

#include "MdiArea.h"
#include <QMdiSubWindow>
#include "Plot.h"
void PlotSettings::dublicateValues()
{
    foreach (QMdiSubWindow* window, MdiArea::getInstance()->subWindowList()) {
        if(!window->isMinimized()){
            dublicateValues(static_cast<Plot*>(window->widget()));
        }
    }
}
