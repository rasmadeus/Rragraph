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
    createProject();
    createRecentlyProjectPaths();
    initAbout();
    createTranslator();
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "Translator.h"
void MainWindow::createTranslator()
{
    translator = new Translator(ui->menuLanguages, this);
    connect(translator, SIGNAL(localeWasChanged()), SLOT(retranslate()));
    translator->tryRestoreLocale();
}

#include <SamplesProxyView.h>
void MainWindow::createSamplesManager()
{
    samplesProxyView = new SamplesProxyView(this);
    connect(ui->actionShowSamplesManager, SIGNAL(triggered()), SLOT(showSamplesProxyView()));
    connect(groups, SIGNAL(hasGroups(bool)), ui->actionShowSamplesManager, SLOT(setEnabled(bool)));
}

#include "PlotSettingsView.h"
void MainWindow::createPlotSettingsView()
{
    PlotSettingsView* plotSettingsView = new PlotSettingsView(this);
    ui->commonSettings->setWidget(plotSettingsView);
    connect(groups, SIGNAL(wasActivated(QMdiSubWindow*)), plotSettingsView, SLOT(catchAndTorturePlot(QMdiSubWindow*)));
    connect(groups, SIGNAL(groupChanged(Group*)), plotSettingsView, SLOT(catchAndTortureGroup(Group*)));
    connect(groups, SIGNAL(noMoreGroup()), plotSettingsView, SLOT(freeGroup()));
    connect(plotSettingsView, SIGNAL(groupNameWasChanged()), groups, SLOT(retitle()));
}

void MainWindow::retranslate()
{
    ui->retranslateUi(this);
    samplesProxyView->retranslate();
    static_cast<PlotSettingsView*>(ui->commonSettings->widget())->retraslate();
    groups->retranslate();
}

void MainWindow::initAbout()
{
    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(showAbout()));
}

#include <QMessageBox>
void MainWindow::showAbout()
{
    QMessageBox::about(
        this,
        tr("About ") + QApplication::applicationName(),
        QApplication::applicationName() + tr(" is a lightweight plotter.") + "<br>" +
        tr("Current version: ") + QApplication::applicationVersion() + "<br>" +
        tr("Developer: ") + "rasmadeus@gmail.com<br>" +
        tr("Testers, generators of ideas: Kojnev A.N, Demin V.N.") + "<br>" +
        "<a href=\"https://github.com/rasmadeus/Rragraph\">" + tr("You can download source code here") + "</a><br>" +
        "<a href=\"http://www.gnu.org/licenses/gpl.en.html\">" + tr("Licence") + " - GPL</a>"
    );
}

#include <QSettings>
void MainWindow::restoreSettings()
{
    QSettings settings("appSettings.ini", QSettings::IniFormat);
    restoreGeometry(settings.value("widgets/MainWindowGeometry").toByteArray());
    restoreState(settings.value("widgets/MainWindowState").toByteArray());
    ui->actionShowExitDialog->setChecked(settings.value("widgets/MainWindowShowExitDialog").toBool());
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
    settings.setValue("widgets/MainWindowShowExitDialog", ui->actionShowExitDialog->isChecked());
}

void MainWindow::createPlotsGroups()
{
    groups = new Groups(this);
    setCentralWidget(groups);
    connect(ui->actionAddOneGroup, SIGNAL(triggered()), groups, SLOT(addGroup()));
    connect(ui->actionCloseAllGroups, SIGNAL(triggered()), groups, SLOT(closeGroups()));
    connect(ui->actionAutoScaleAllPlots, SIGNAL(triggered()), groups, SLOT(autoScaleActiveGroup()));
    connect(ui->actionExportAllGroupsToImages, SIGNAL(triggered()), groups, SLOT(exportToPng()));
    connect(groups, SIGNAL(hasGroups(bool)), ui->menuPlots, SLOT(setEnabled(bool)));
    connect(groups, SIGNAL(hasGroups(bool)), ui->toolBarPlots, SLOT(setEnabled(bool)));
    connect(groups, SIGNAL(hasGroups(bool)), ui->menuPlotsTiling, SLOT(setEnabled(bool)));
    connect(groups, SIGNAL(groupChanged(Group*)), SLOT(setActiveActionOfTilingMenu(Group*)));
}

void MainWindow::routePlotsMenu()
{
    connect(ui->actionAddPlot, SIGNAL(triggered()), groups, SLOT(addPlot()));
    connect(ui->actionCloseAllPlots, SIGNAL(triggered()), groups, SLOT(clearActiveGroup()));
    connect(ui->actionTile, SIGNAL(triggered()), groups, SLOT(tileActiveGroup()));
    connect(ui->actionExportPlotsToImages, SIGNAL(triggered()), groups, SLOT(exportActiveGroupToPng()));
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
    connect(tilingMenu, SIGNAL(triggered(QAction*)), groups, SLOT(setGroupTiling(QAction*)));
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

void MainWindow::showSamplesProxyView()
{
    samplesProxyView->setSamplesManager(groups->getGroup()->getSamplesManager());
    samplesProxyView->show();
}

#include "Project.h"
void MainWindow::createProject()
{
    project = new Project(groups, this);
    connect(ui->actionLoadProject, SIGNAL(triggered()), project, SLOT(load()));
    connect(ui->actionReloadProject, SIGNAL(triggered()), project, SLOT(reload()));
    connect(ui->actionSaveProject, SIGNAL(triggered()), project, SLOT(save()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), project, SLOT(saveAs()));
    connect(ui->actionClose, SIGNAL(triggered()), project, SLOT(close()));
    connect(project, SIGNAL(wasReplaced(QString)), SLOT(setWindowTitle(QString)));
    connect(project, SIGNAL(wasClosed()), SLOT(restoreWindowTitle()));
}

void MainWindow::restoreWindowTitle()
{
    setWindowTitle(tr("Rragraph - lightweight plotter"));
}

#include "RecentlyProjectPaths.h"
void MainWindow::createRecentlyProjectPaths()
{
    recentlyProjectPaths = new RecentlyProjectPaths(ui->menuProject);
    connect(recentlyProjectPaths, SIGNAL(triggered(QAction*)), project, SLOT(load(QAction*)));
    connect(ui->menuProject, SIGNAL(aboutToShow()), SLOT(fillProjectMenu()));
    connect(project, SIGNAL(wasReplaced(QString)), recentlyProjectPaths, SLOT(appendPath(QString)));
}

void MainWindow::fillProjectMenu()
{
    ui->menuProject->clear();
    ui->menuProject->addAction(ui->actionLoadProject);
    ui->menuProject->addAction(ui->actionReloadProject);
    recentlyProjectPaths->update(ui->menuProject);
    ui->menuProject->addAction(ui->actionSaveProject);
    ui->menuProject->addAction(ui->actionSaveAs);
    ui->menuProject->addSeparator();
    ui->menuProject->addAction(ui->actionClose);
}

#include "ExitMessage.h"
#include <QCloseEvent>
void MainWindow::closeEvent(QCloseEvent* event)
{
    if(ui->actionShowExitDialog->isChecked()){
        ExitMessage exitMessage;
        switch(exitMessage.exec()){
            case ExitMessage::SAVE_PROJECT_AND_EXIT:
                if(!project->save()){
                    event->ignore();
                    return;
                }
                break;
            case ExitMessage::GO_BACK:
                event->ignore();
                return;
            default:
                break;
            }
    }
    /*!
     * \brief saveSettings - Если сохранять настройки в деструкторе, тогда
     * будет отеряно свойство видимости открепляемых виджетов.
     * Поэтому вызываем отсюда.
     */
    saveSettings();
    return QMainWindow::closeEvent(event);
}


#include <SamplesManager.h>
void MainWindow::processArgs(const QStringList& args)
{
    auto i = std::find_if(
       args.begin(),
       args.end(),
       [&](const QString& path){
           return QFileInfo(path).suffix().toLower() == "rgf";
        }
    );
    if(i != args.end()){
        project->load(*i);
    }
    else{
        groups->addGroup()->getSamplesManager()->append(args);
    }
}

#include <QDropEvent>
#include <QMimeData>
void MainWindow::dropEvent(QDropEvent* evt)
{
    if(evt->mimeData()->hasUrls()){
        QStringList paths;
        foreach(const QUrl& url, evt->mimeData()->urls()){
            paths << url.toLocalFile();
        }
        processArgs(paths);
    }
}

#include <QDragEnterEvent>
void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if(event->mimeData()->hasFormat("text/uri-list")){
        event->acceptProposedAction();
    }
}
