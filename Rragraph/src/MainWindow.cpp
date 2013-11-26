#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Files.h"
#include "HeadersView.h"
#include "MdiArea.h"
#include "PlotSettingsView.h"
#include "CurveSettingsView.h"
#include <QSettings>
#include "Project.h"
#include "HeaderSamples.h"
#include "FilesModel.h"
#include "Translator.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    Files::make(this);
    FilesModel::make(this);
    MdiArea::make(this);
    CurveSettingsView::make(this);
    HeaderSamples::make(this);
    Project::make(this);

    Translator::make(this);
    Translator::getInstance()->fill(ui->menuLanguages);
    connect(Translator::getInstance(), SIGNAL(localeWasChanged()), SLOT(localeWasChanged()));

    files            = Files::getInstance();
    mdiArea          = MdiArea::getInstance();
    project          = Project::getInstance();
    headersView      = new HeadersView(this);
    plotSettings     = new PlotSettingsView();
    lastProjectPaths = new QActionGroup(this);
    tileBehavior     = new QActionGroup(this);

    ui->actionGridHorizontal->setData(MdiArea::GRID_HORIZONTAL);
    ui->actionVerticalStraight->setData(MdiArea::VERTICAL_STRAIGHT);
    ui->actionVerticalReverse->setData(MdiArea::VERTICAL_REVERSE);

    tileBehavior->addAction(ui->actionGridHorizontal);
    tileBehavior->addAction(ui->actionVerticalStraight);
    tileBehavior->addAction(ui->actionVerticalReverse);
    ui->menuTileBehavior->addActions(tileBehavior->actions());

    fillProjectMenu();

    ui->menuProject->insertActions(ui->actionSave, lastProjectPaths->actions());
    ui->menuProject->insertSeparator(ui->actionSave);
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

    connect(ui->menuProject, SIGNAL(aboutToShow()), SLOT(fillProjectMenu()));

    connect(ui->actionAddFiles, SIGNAL(triggered()), files,   SLOT(load()));

    connect(ui->actionInsertPlot,      SIGNAL(triggered()),         mdiArea, SLOT(insertPlot()));
    connect(ui->actionTile,            SIGNAL(triggered()),         mdiArea, SLOT(tile()));
    connect(ui->actionCascade,         SIGNAL(triggered()),         mdiArea, SLOT(cascadeSubWindows()));
    connect(ui->actionCloseAllWindows, SIGNAL(triggered()),         mdiArea, SLOT(closeAllSubWindows()));
    connect(ui->actionPngExport,       SIGNAL(triggered()),         mdiArea, SLOT(exportToPng()));
    connect(ui->actionPrint,           SIGNAL(triggered()),         mdiArea, SLOT(print()));
    connect(ui->actionAutoScale,       SIGNAL(triggered()),         mdiArea, SLOT(autoscale()));
    connect(tileBehavior,              SIGNAL(triggered(QAction*)), mdiArea, SLOT(changeTileType(QAction*)));

    connect(ui->actionLoad,         SIGNAL(triggered()),         project, SLOT(load()));
    connect(ui->actionSaveAs,       SIGNAL(triggered()),         project, SLOT(saveAs()));
    connect(ui->actionSave,         SIGNAL(triggered()),         project, SLOT(save()));
    connect(ui->actionReload,       SIGNAL(triggered()),         project, SLOT(reload()));
    connect(ui->actionCloseProject, SIGNAL(triggered()),         project, SLOT(close()));
    connect(lastProjectPaths,       SIGNAL(triggered(QAction*)), project, SLOT(loadProjectFrom(QAction*)));

    connect(project, SIGNAL(wasLoadedFrom(QString)),   SLOT(setWindowTitle(QString)));
    connect(project, SIGNAL(wasClosed(QString)),       SLOT(setWindowTitle(QString)));
    connect(project, SIGNAL(wasSavedAs(QString)),      SLOT(setWindowTitle(QString)));
    connect(project, SIGNAL(lastLoadedPathsChanged()), SLOT(fillProjectMenu()));

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

void MainWindow::localeWasChanged()
{
    ui->retranslateUi(this);
    plotSettings->localeWasChanged();
    mdiArea->localeWasChanged();
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

void MainWindow::fillProjectMenu()
{
    ui->menuProject->clear();
    ui->menuProject->addAction(ui->actionLoad);
    ui->menuProject->addAction(ui->actionReload);
    ui->menuProject->addSeparator();
    ui->menuProject->addAction(ui->actionSave);
    ui->menuProject->addAction(ui->actionSaveAs);
    ui->menuProject->addSeparator();
    addLastProjectPaths();
    ui->menuProject->addAction(ui->actionCloseProject);
}

static QString getReduceLastPath(const QString& path)
{
    QStringList parts = path.split("/");
    if(parts.size() >= 2){
        return ".../" + parts[parts.size() - 2] + "/" + parts[parts.size() - 1];
    }
    return path;
}

void MainWindow::addLastProjectPaths()
{
    const QStringList paths = Project::getInstance()->lastLoadedPaths();
    foreach(QAction* action, lastProjectPaths->actions()){
        lastProjectPaths->removeAction(action);
    }

    foreach(const QString& path, paths){
        QAction* action = new QAction(getReduceLastPath(path), lastProjectPaths);
        action->setData(path);
        action->setStatusTip(path);
        lastProjectPaths->addAction(action);
    }

    ui->menuProject->addActions(lastProjectPaths->actions());

    if(!paths.isEmpty()){
        ui->menuProject->addSeparator();
    }
}

#include <QDragEnterEvent>
#include <QMimeData>
void MainWindow::dragEnterEvent(QDragEnterEvent* evt)
{
    if(evt->mimeData()->hasFormat("text/uri-list")){
        evt->acceptProposedAction();
    }
}

#include <QDropEvent>
void MainWindow::dropEvent(QDropEvent* evt)
{
    if(evt->mimeData()->hasUrls()){
        QStringList paths;
        foreach(QUrl url, evt->mimeData()->urls()){
            paths << url.toLocalFile();
        }
        Project::getInstance()->load(paths);
    }
}
