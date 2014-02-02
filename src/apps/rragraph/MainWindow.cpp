#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "PlotsGroups.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createPlotsGroups();
    routePlotsMenu();
    createPlotsTilingMenu();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createPlotsGroups()
{
    plotsGroups = new PlotsGroups(this);
    setCentralWidget(plotsGroups);
    connect(ui->actionAddOneGroup, SIGNAL(triggered()), plotsGroups, SLOT(addPlots()));
    connect(ui->actionCloseAllGroups, SIGNAL(triggered()), plotsGroups, SLOT(closeGroups()));
    connect(ui->actionAutoScaleAllPlots, SIGNAL(triggered()), plotsGroups, SLOT(autoScaleActiveGroup()));
    connect(ui->actionExportAllGroupsToImages, SIGNAL(triggered()), plotsGroups, SLOT(exportToPng()));
    connect(plotsGroups, SIGNAL(hasGroups(bool)), ui->menuPlots, SLOT(setEnabled(bool)));
    connect(plotsGroups, SIGNAL(hasGroups(bool)), ui->toolBarPlots, SLOT(setEnabled(bool)));
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

