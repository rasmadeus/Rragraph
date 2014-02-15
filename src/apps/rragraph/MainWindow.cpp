#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Groups.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createPlotsGroups();
    routePlotsMenu();
    createPlotsTilingMenu();
    createPlotSettingsView();
    restoreVisibilityActionsState();
    restoreSettings();
    createSamplesManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QSettings>
void MainWindow::restoreSettings()
{
    QSettings settings("appSettings.ini", QSettings::IniFormat);
    restoreGeometry(settings.value("widgets/MainWindowGeometry").toByteArray());
    restoreState(settings.value("widgets/MainWindowState").toByteArray());
}

void MainWindow::restoreVisibilityActionsState()
{

    ui->actionVisibilityGroupsToolBar->setChecked(ui->toolBarGroups->isVisible());
    ui->actionVisibilityPlotsToolBar->setChecked(ui->toolBarPlots->isVisible());
}

void MainWindow::saveSettings()
{
    QSettings settings("appSettings.ini", QSettings::IniFormat);
    settings.setValue("widgets/MainWindowGeometry", saveGeometry());
    settings.setValue("widgets/MainWindowState", saveState());
}

void MainWindow::createPlotsGroups()
{
    plotsGroups = new Groups(this);
    setCentralWidget(plotsGroups);
    connect(ui->actionAddOneGroup, SIGNAL(triggered()), plotsGroups, SLOT(addPlots()));
    connect(ui->actionCloseAllGroups, SIGNAL(triggered()), plotsGroups, SLOT(closeGroups()));
    connect(ui->actionAutoScaleAllPlots, SIGNAL(triggered()), plotsGroups, SLOT(autoScaleActiveGroup()));
    connect(ui->actionExportAllGroupsToImages, SIGNAL(triggered()), plotsGroups, SLOT(exportToPng()));
    connect(plotsGroups, SIGNAL(hasGroups(bool)), ui->menuPlots, SLOT(setEnabled(bool)));
    connect(plotsGroups, SIGNAL(hasGroups(bool)), ui->toolBarPlots, SLOT(setEnabled(bool)));
    connect(plotsGroups, SIGNAL(hasGroups(bool)), ui->menuPlotsTiling, SLOT(setEnabled(bool)));
    connect(plotsGroups, SIGNAL(groupChanged(Group*)), SLOT(setActiveActionOfTilingMenu(Group*)));
}

void MainWindow::routePlotsMenu()
{
    connect(ui->actionAddPlot, SIGNAL(triggered()), plotsGroups, SLOT(addPlot()));
    connect(ui->actionCloseAllPlots, SIGNAL(triggered()), plotsGroups, SLOT(clearActiveGroup()));
    connect(ui->actionTile, SIGNAL(triggered()), plotsGroups, SLOT(tileActiveGroup()));
    connect(ui->actionExportPlotsToImages, SIGNAL(triggered()), plotsGroups, SLOT(exportActiveGroupToPng()));
}

#include <QActionGroup>
#include "Group.h"
void MainWindow::createPlotsTilingMenu()
{
    ui->actionGridHorizontal->setData(Group::GRID_HORIZONTAL);
    ui->actionVerticalReverse->setData(Group::VERTICAL_REVERSE);
    ui->actionVerticalStraight->setData(Group::VERTICAL_STRAIGHT);
    QActionGroup* tilingMenu = new QActionGroup(ui->menuPlotsTiling);
    tilingMenu->addAction(ui->actionGridHorizontal);
    tilingMenu->addAction(ui->actionVerticalStraight);
    tilingMenu->addAction(ui->actionVerticalReverse);
    ui->menuPlotsTiling->addActions(tilingMenu->actions());
    connect(tilingMenu, SIGNAL(triggered(QAction*)), plotsGroups, SLOT(setGroupTiling(QAction*)));
}

void MainWindow::setActiveActionOfTilingMenu(Group* plots)
{
    switch(plots->getTileType()){
        case Group::GRID_HORIZONTAL: ui->actionGridHorizontal->setChecked(true); break;
        case Group::VERTICAL_REVERSE: ui->actionVerticalReverse->setChecked(true); break;
        case Group::VERTICAL_STRAIGHT: ui->actionVerticalStraight->setChecked(true); break;
        default: ui->actionGridHorizontal->setChecked(true); break;
    }
}

#include "PlotSettingsView.h"
void MainWindow::createPlotSettingsView()
{
    PlotSettingsView* plotSettingsView = new PlotSettingsView(this);
    ui->commonSettings->setWidget(plotSettingsView);
    connect(plotsGroups, SIGNAL(wasActivated(QMdiSubWindow*)), plotSettingsView, SLOT(catchAndTorturePlot(QMdiSubWindow*)));
    connect(plotsGroups, SIGNAL(groupChanged(Group*)), plotSettingsView, SLOT(catchAndTortureGroup(Group*)));
    connect(plotsGroups, SIGNAL(noMoreGroup()), plotSettingsView, SLOT(freeGroup()));
    connect(plotSettingsView, SIGNAL(groupNameWasChanged()), plotsGroups, SLOT(retitle()));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    /*!
     * \brief saveSettings - Если сохранять настройки в деструкторе, тогда
     * будет отеряно свойство видимости открепляемых виджетов.
     * Поэтому вызываем отсюда.
     */
    saveSettings();
    return QMainWindow::closeEvent(event);
}

#include <SamplesProxyView.h>
void MainWindow::createSamplesManager()
{
    samplesProxyView = new SamplesProxyView(this);
    connect(ui->actionShowSamplesManager, SIGNAL(triggered()), SLOT(showSamplesProxyView()));
    connect(plotsGroups, SIGNAL(hasGroups(bool)), ui->actionShowSamplesManager, SLOT(setEnabled(bool)));
}

void MainWindow::showSamplesProxyView()
{
    samplesProxyView->setSamplesManager(plotsGroups->getGroup()->getSamplesManager());
    samplesProxyView->show();
}
