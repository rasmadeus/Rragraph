#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Files.h"
#include "HeadersView.h"
#include "MdiArea.h"
#include "PlotSettingsView.h"
#include "CurveSettingsView.h"
#include <QSettings>
#include "Project.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MdiArea::create(this);
    CurveSettingsView::create(this);

    files        = Files::getInstance(this);
    mdiArea      = MdiArea::getInstance();
    headersView  = new HeadersView(this);
    plotSettings = new PlotSettingsView(this);
    project      = new Project(this);

    ui->headers->setWidget(headersView);
    ui->plotSettings->setWidget(plotSettings);
    setCentralWidget(mdiArea);

    ui->headers->setVisible(false);

    connect(
        mdiArea,
        SIGNAL(subWindowActivated(QMdiSubWindow*)),
        plotSettings,
        SLOT(setOwner(QMdiSubWindow*))
    );


    connect(ui->actionAddFiles,        SIGNAL(triggered()), files,   SLOT(load()));

    connect(ui->actionInsertPlot,      SIGNAL(triggered()), mdiArea, SLOT(insertPlot()));
    connect(ui->actionTile,            SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));
    connect(ui->actionCascade,         SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));
    connect(ui->actionCloseAllWindows, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));
    connect(ui->actionPngExport,       SIGNAL(triggered()), mdiArea, SLOT(exportToPng()));
    connect(ui->actionPrint,           SIGNAL(triggered()), mdiArea, SLOT(print()));
    connect(ui->actionAutoScale,       SIGNAL(triggered()), mdiArea, SLOT(autoscale()));

    connect(ui->actionLoad,   SIGNAL(triggered()), project, SLOT(load()));
    connect(ui->actionSaveAs,   SIGNAL(triggered()), project, SLOT(saveAs()));

    QSettings s;
    s.beginGroup("MainWindow");
        restoreGeometry(s.value("geometry").toByteArray());
        restoreState(s.value("state").toByteArray());
        ui->actionShowProjectsToolBar->setChecked(ui->projectsToolBar->isVisible());
    s.endGroup();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* evt)
{
    QSettings s;
    s.beginGroup("MainWindow");
        s.setValue("geometry", saveGeometry());
        s.setValue("state", saveState());
    s.endGroup();
    QMainWindow::closeEvent(evt);
}
