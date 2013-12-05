#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    initFiles();
    initMdiArea();
    initSingletons();
    initProject();
    initTranslator();
    initProjectPaths();
    initTileBahavior();
    initDockWidgets();
    initExitMessage();
    initHelper();
    fillProjectMenu();
    initLookAndFeel();
}

#include "Files.h"
#include "FilesModel.h"
void MainWindow::initFiles()
{
//1.
    Files::make(this);
    files = Files::getInstance();
    connect(ui->actionAddFiles, SIGNAL(triggered()), files, SLOT(load()));
//2.
    FilesModel::make(this);
}

#include "MdiArea.h"
void MainWindow::initMdiArea()
{
//1.
    MdiArea::make(this);
    mdiArea = MdiArea::getInstance();
//2.
    setCentralWidget(mdiArea);
//3.
    connect(ui->actionInsertPlot,      SIGNAL(triggered()), mdiArea, SLOT(insertPlot()));
    connect(ui->actionTile,            SIGNAL(triggered()), mdiArea, SLOT(tile()));
    connect(ui->actionCascade,         SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));
    connect(ui->actionCloseAllWindows, SIGNAL(triggered()), mdiArea, SLOT(closeAllSubWindows()));
    connect(ui->actionPngExport,       SIGNAL(triggered()), mdiArea, SLOT(exportToPng()));
    connect(ui->actionPrint,           SIGNAL(triggered()), mdiArea, SLOT(print()));
    connect(ui->actionAutoScale,       SIGNAL(triggered()), mdiArea, SLOT(autoscale()));
}

#include "CurveSettingsView.h"
#include "HeaderSamples.h"
void MainWindow::initSingletons()
{
    CurveSettingsView::make(this);
    HeaderSamples::make(this);
    connect(mdiArea, SIGNAL(noMoreWindow(Plot*)), CurveSettingsView::getInstance(), SLOT(setOwner(Plot*)));
}

#include "Project.h"
void MainWindow::initProject()
{
//1.
    Project::make(this);
    project = Project::getInstance();
//2.
    connect(ui->actionLoad,            SIGNAL(triggered()), project, SLOT(load()));
    connect(ui->actionSaveAs,          SIGNAL(triggered()), project, SLOT(saveAs()));
    connect(ui->actionSave,            SIGNAL(triggered()), project, SLOT(save()));
    connect(ui->actionReload,          SIGNAL(triggered()), project, SLOT(reload()));
    connect(ui->actionCloseProject,    SIGNAL(triggered()), project, SLOT(close()));
    connect(ui->actionCopyProjectFile, SIGNAL(triggered()), project, SLOT(copyProjectFile()));
//3.
    connect(project, SIGNAL(wasLoadedFrom(QString)),   SLOT(setWindowTitle(QString)));
    connect(project, SIGNAL(wasClosed(QString)),       SLOT(setWindowTitle(QString)));
    connect(project, SIGNAL(wasSavedAs(QString)),      SLOT(setWindowTitle(QString)));
    connect(project, SIGNAL(lastLoadedPathsChanged()), SLOT(fillProjectMenu()));
}

#include "Translator.h"
void MainWindow::initTranslator()
{
    Translator::make(this);
    Translator::getInstance()->fill(ui->menuLanguages);
    connect(Translator::getInstance(), SIGNAL(localeWasChanged()), SLOT(localeWasChanged()));
}

#include "PlotSettingsView.h"
void MainWindow::localeWasChanged()
{
    ui->retranslateUi(this);
    plotSettings->localeWasChanged();
    mdiArea->localeWasChanged();
}

void MainWindow::initProjectPaths()
{
//1.
    lastProjectPaths = new QActionGroup(this);
    connect(lastProjectPaths, SIGNAL(triggered(QAction*)), project, SLOT(loadProjectFrom(QAction*)));
//2.
    ui->menuProject->insertActions(ui->actionSave, lastProjectPaths->actions());
    ui->menuProject->insertSeparator(ui->actionSave);
    connect(ui->menuProject, SIGNAL(aboutToShow()), SLOT(fillProjectMenu()));    
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
    ui->menuProject->addAction(ui->actionCopyProjectFile);
    ui->menuProject->addAction(ui->actionCloseProject);
}

void MainWindow::initTileBahavior()
{
//1.
    tileBehavior = new QActionGroup(this);
//2.
    ui->actionGridHorizontal->setData(MdiArea::GRID_HORIZONTAL);
    ui->actionVerticalStraight->setData(MdiArea::VERTICAL_STRAIGHT);
    ui->actionVerticalReverse->setData(MdiArea::VERTICAL_REVERSE);
//3.
    tileBehavior->addAction(ui->actionGridHorizontal);
    tileBehavior->addAction(ui->actionVerticalStraight);
    tileBehavior->addAction(ui->actionVerticalReverse);
    ui->menuTileBehavior->addActions(tileBehavior->actions());
//4.
    connect(tileBehavior, SIGNAL(triggered(QAction*)), mdiArea, SLOT(changeTileType(QAction*)));
}

#include "HeadersView.h"
void MainWindow::initDockWidgets()
{
//1.
    headersView  = new HeadersView(this);
    ui->headers->setWidget(headersView);
    ui->headers->setVisible(false);
//2.
    plotSettings = new PlotSettingsView(this);
    ui->plotSettings->setWidget(plotSettings);
    connect(
        mdiArea,
        SIGNAL(subWindowActivated(QMdiSubWindow*)),
        plotSettings,
        SLOT(setOwner(QMdiSubWindow*))
    );
}

#include <QSettings>
void MainWindow::initLookAndFeel()
{
    QSettings s;
    s.beginGroup("MainWindow");
        restoreGeometry(s.value("geometry").toByteArray());
        restoreState(s.value("state").toByteArray());
        ui->actionShowProjectsToolBar->setChecked(ui->projectsToolBar->isVisible());
    s.endGroup();
}

#include "ExitMessage.h"
void MainWindow::initExitMessage()
{
    ui->actionShowExitDialog->setChecked(ExitMessage::messageIsVisible());
    connect(ui->actionShowExitDialog, SIGNAL(triggered(bool)), SLOT(setExitMessageVisibility(bool)));
}

void MainWindow::setExitMessageVisibility(bool isVisible){
    ExitMessage::setMessageVisible(isVisible);
}

#include <QFileDialog>
void MainWindow::initHelper(){
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(showAbout()));
}

#include <QMessageBox>
void MainWindow::showAbout()
{
    QMessageBox::about(
        this,
        tr("About Rragraph"),
        tr(
            "Rragraph is a lightweight plotter. <br>"
            "Current version 4.0.<br>"
            "Developer: rasmadeus@gmail.com<br>"
            "<a href=\"https://github.com/rasmadeus/Rragraph\">You can download source code here</a><br>"
            "<a href=\"http://www.gnu.org/licenses/gpl.en.html\">Licence - GPL</a>"
        )
    );
}

MainWindow::~MainWindow(){
    delete ui;
}

#include <QCloseEvent>
void MainWindow::closeEvent(QCloseEvent* evt)
{
//1.
    if(ui->actionShowExitDialog->isChecked()){
        ExitMessage exitMessage;
        switch(exitMessage.exec()){
            case ExitMessage::SAVE_PROJECT_AND_EXIT:
                if(Project::getInstance()->save()){
                    break;
                }
                evt->ignore();
                return;
            case ExitMessage::DO_NOT_SAVE_PROJECT_AND_EXIT:
                break;
            case ExitMessage::GO_BACK:
                evt->ignore();
                return;
            default:
                evt->ignore();
                return;
        }
    }
//2.
    QSettings s;
    s.beginGroup("MainWindow");
        s.setValue("geometry", saveGeometry());
        s.setValue("state", saveState());
    s.endGroup();
//3.
    QMainWindow::closeEvent(evt);
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
        foreach(const QUrl& url, evt->mimeData()->urls()){
            paths << url.toLocalFile();
        }
        Project::getInstance()->load(paths);
    }
}
