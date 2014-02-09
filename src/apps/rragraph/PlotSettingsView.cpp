#include "PlotSettingsView.h"
#include "ui_PlotSettingsView.h"

PlotSettingsView::PlotSettingsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlotSettingsView),
    plot(nullptr),
    catchAble(true),
    group(nullptr)
{
    ui->setupUi(this);
    createGroupSettings();
    createSettingsWidgets();
    addSettingsWidgetToForm();
    listenSettingsWidget();
}

PlotSettingsView::~PlotSettingsView()
{
    delete ui;
}

#include <QMdiSubWindow>
void PlotSettingsView::catchAndTorturePlot(QMdiSubWindow* window)
{
    if(catchAble){
        if(window){
            toNewState(window);
        }
        else{
            toDefaultState();
        }
    }
}

#include "GroupSettings.h"
void PlotSettingsView::createGroupSettings()
{
    groupSettings = new GroupSettings(this);
    ui->mainLayout->addWidget(groupSettings);
    connect(groupSettings, SIGNAL(groupNameWasChanged()), SIGNAL(groupNameWasChanged()));
}

#include "Group.h"
void PlotSettingsView::catchAndTortureGroup(Group* group)
{
    if(catchAble){
        this->group = group;
        if(group){
            if(group->isEmpty()){
                catchAndTorturePlot(nullptr);
            }
            groupSettings->setGroup(group);
            groupSettings->setEnabled(true);
        }
        else{
            groupSettings->setEnabled(false);
            catchAndTorturePlot(nullptr);
        }
    }
}

void PlotSettingsView::freeGroup()
{
    groupSettings->setEnabled(false);
    catchAndTortureGroup(nullptr);
}

void PlotSettingsView::lockPlot()
{
    catchAble = false;
}

void PlotSettingsView::unlockPlot()
{
    catchAble = true;
}

#include "PlotWithCurves.h"
#include "PlotSettings.h"
void PlotSettingsView::toNewState(QMdiSubWindow* window)
{
    plot = static_cast<PlotWithCurves*>(window->widget());
    foreach(PlotSettings* plotSettings, settings){
        plotSettings->setEasyMark(plot);
    }
}

void PlotSettingsView::toDefaultState()
{
    plot = nullptr;
    foreach(PlotSettings* plotSettings, settings){
        plotSettings->toDefaultState();
    }
}

void PlotSettingsView::addSettingsWidgetToForm()
{
    foreach(PlotSettings* plotSettings, settings){
        ui->mainLayout->addWidget(plotSettings);
    }
}

void PlotSettingsView::listenSettingsWidget()
{
    foreach(PlotSettings* plotSettings, settings){
        connect(plotSettings, SIGNAL(copyFrom(PlotSettings*)), SLOT(dublicateSettingsToGroup(PlotSettings*)));
        connect(plotSettings, SIGNAL(catchPlot()), SLOT(lockPlot()));
        connect(plotSettings, SIGNAL(freePlot()), SLOT(unlockPlot()));
    }
}

#include "CommonPlotSettings.h"
#include "AxisPlotSettings.h"
#include "ExportPlotSettings.h"
#include "LegendPlotSettings.h"
void PlotSettingsView::createSettingsWidgets()
{
    settings
        << new CommonPlotSettings(this)
        << new AxisPlotSettings(QwtPlot::xBottom, this)
        << new AxisPlotSettings(QwtPlot::yLeft, this)
        << new ExportPlotSettings(this)
        << new LegendPlotSettings(this);
}

void PlotSettingsView::dublicateSettingsToGroup(PlotSettings* plotSettings)
{
    group->dublicateSettings(plotSettings);
}
