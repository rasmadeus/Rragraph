#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Groups.h"
#include <Settings.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    Settings::create(QApplication::applicationDirPath() + "/appSettings.ini");
    ui->setupUi(this);    
    createPlotsGroups();
    routePlotsMenu();
    createPlotsTilingMenu();
    createPlotSettingsView();
    restoreVisibilityActionsState();
    restoreSettings();
    createProject();
    createSamplesProxyActions();
    createRecentlyProjectPaths();
    initAbout();
    createTranslator();
}

#include "GroupSettings.h"
#include <PlotSettings.h>
#include "Project.h"
#include "Translator.h"
#include "RecentlyProjectPaths.h"
MainWindow::~MainWindow()
{
    delete project;
    delete plotSettings;
    delete groupSettings;
    delete translator;
    delete groups;
    delete recentlyProjectPaths;
    delete ui;
    Settings::destroy();
}

void MainWindow::createTranslator()
{
    translator = new Translator(ui->menuLanguages, this);
    connect(translator, SIGNAL(localeWasChanged()), SLOT(retranslate()));
    translator->tryRestoreLocale();
}

#include <QVBoxLayout>
#include <QScrollArea>
#include <QSpacerItem>
void MainWindow::createPlotSettingsView()
{
    groupSettings = new GroupSettings(this);
    plotSettings = new PlotSettings(this);
    {
        QScrollArea* scroller = new QScrollArea(this);      
        QVBoxLayout* content = new QVBoxLayout(scroller->viewport());
        content->setMargin(0);
        content->setSpacing(0);
        content->addWidget(groupSettings);
        content->addWidget(plotSettings);
        ui->commonSettings->setWidget(scroller);
    }
    {
        connect(groupSettings, SIGNAL(groupNameWasChanged()),             groups,        SLOT(retitle()));
        connect(groups,        SIGNAL(groupChanged(Group*)),              groupSettings, SLOT(catchGroup(Group*)));
        connect(groups,        SIGNAL(noMoreGroup()),                     groupSettings, SLOT(freeGroup()));
        connect(groups,        SIGNAL(wasActivated(QMdiSubWindow*)),      plotSettings,  SLOT(catchPlot(QMdiSubWindow*)));
        connect(groups,        SIGNAL(noMoreGroup()),                     plotSettings,  SLOT(toDefaultState()));
        connect(groups,        SIGNAL(noMorePlots()),                     plotSettings,  SLOT(toDefaultState()));
        connect(plotSettings,  SIGNAL(copySettings(PlotSettingsFiller*)), groups,        SLOT(copySettingsToActiveGroup(PlotSettingsFiller*)));
    }
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

#include <QApplication>
void MainWindow::restoreSettings()
{
    restoreGeometry(Settings::obj()->get("widgets/MainWindowGeometry").toByteArray());
    restoreState(Settings::obj()->get("widgets/MainWindowState").toByteArray());
    ui->actionShowExitDialog->setChecked(Settings::obj()->get("widgets/MainWindowShowExitDialog").toBool());
    ui->actionAskAboutDanger->setChecked(Settings::obj()->get("widgets/MainWindowAskAboutDanger").toBool());
}

void MainWindow::restoreVisibilityActionsState()
{
    ui->actionVisibilityGroupsToolBar->setChecked(ui->toolBarGroups->isVisible());
    ui->actionVisibilityPlotsToolBar->setChecked(ui->toolBarPlots->isVisible());
    ui->actionVisibilityCommonSettings->setChecked(ui->commonSettings->isVisible());
}


void MainWindow::saveSettings()
{
    Settings::obj()->set("widgets/MainWindowGeometry", saveGeometry());
    Settings::obj()->set("widgets/MainWindowState", saveState());
    Settings::obj()->set("widgets/MainWindowShowExitDialog", ui->actionShowExitDialog->isChecked());
    Settings::obj()->set("widgets/MainWindowAskAboutDanger", ui->actionAskAboutDanger->isChecked());
}

void MainWindow::createPlotsGroups()
{
    groups = new Groups(this);
    setCentralWidget(groups);
    {
        connect(ui->actionCloseAllGroups, SIGNAL(triggered()), SLOT(tryClearGroups()));
    }
    {
        connect(ui->actionAddOneGroup,             SIGNAL(triggered()), groups, SLOT(addGroup()));
        connect(ui->actionAutoScaleAllPlots,       SIGNAL(triggered()), groups, SLOT(autoScaleActiveGroup()));
        connect(ui->actionExportAllGroupsToImages, SIGNAL(triggered()), groups, SLOT(exportToPng()));
    }
    {
        connect(groups, SIGNAL(hasGroups(bool)), ui->menuPlots,       SLOT(setEnabled(bool)));
        connect(groups, SIGNAL(hasGroups(bool)), ui->toolBarPlots,    SLOT(setEnabled(bool)));
        connect(groups, SIGNAL(hasGroups(bool)), ui->menuPlotsTiling, SLOT(setEnabled(bool)));
    }
    {
        connect(groups, SIGNAL(groupChanged(Group*)), SLOT(setActiveActionOfTilingMenu(Group*)));
        connect(groups, SIGNAL(beginExport()),        SLOT(beginWaiting()));
        connect(groups, SIGNAL(endExport()),          SLOT(endWaiting()));
    }
}

void MainWindow::routePlotsMenu()
{
    {
        connect(ui->actionCloseAllPlots, SIGNAL(triggered()), SLOT(tryClearWindows()));
    }
    {
        connect(ui->actionAddPlot,             SIGNAL(triggered()), groups, SLOT(addPlot()));
        connect(ui->actionTile,                SIGNAL(triggered()), groups, SLOT(tileActiveGroup()));
        connect(ui->actionExportPlotsToImages, SIGNAL(triggered()), groups, SLOT(exportActiveGroupToPng()));
        connect(ui->actionExportPlotsToPdf,    SIGNAL(triggered()), groups, SLOT(exportActiveGroupToPdf()));
    }

}

#include <QActionGroup>
#include "Group.h"
void MainWindow::createPlotsTilingMenu()
{
    {
        ui->actionGridHorizontal->setData(Group::GRID_STRAIGHT);
        ui->actionGridReverse->setData(Group::GRID_REVERSE);
        ui->actionVerticalReverse->setData(Group::VERTICAL_REVERSE);
        ui->actionVerticalStraight->setData(Group::VERTICAL_STRAIGHT);
    }
    QActionGroup* tilingMenu = new QActionGroup(ui->menuPlotsTiling);
    {
        tilingMenu->addAction(ui->actionGridHorizontal);
        tilingMenu->addAction(ui->actionGridReverse);
        tilingMenu->addAction(ui->actionVerticalStraight);
        tilingMenu->addAction(ui->actionVerticalReverse);
    }
    {
        ui->menuPlotsTiling->addActions(tilingMenu->actions());
        connect(tilingMenu, SIGNAL(triggered(QAction*)), groups, SLOT(setGroupTiling(QAction*)));
    }
}

void MainWindow::setActiveActionOfTilingMenu(Group* plots)
{
    switch(plots->getTileType()){
        case Group::GRID_STRAIGHT: ui->actionGridHorizontal->setChecked(true); break;
        case Group::GRID_REVERSE: ui->actionGridReverse->setChecked(true); break;
        case Group::VERTICAL_REVERSE: ui->actionVerticalReverse->setChecked(true); break;
        case Group::VERTICAL_STRAIGHT: ui->actionVerticalStraight->setChecked(true); break;
        default: ui->actionGridHorizontal->setChecked(true); break;
    }
}


void MainWindow::createProject()
{
    project = new Project(groups, this);
    {
        connect(ui->actionReloadProject,    SIGNAL(triggered()), SLOT(tryReloadProject()));
        connect(ui->actionClose,            SIGNAL(triggered()), SLOT(tryCloseProject()));
    }
    {
        connect(ui->actionLoadProject,      SIGNAL(triggered()), project, SLOT(load()));
        connect(ui->actionSaveProject,      SIGNAL(triggered()), project, SLOT(save()));
        connect(ui->actionSaveAs,           SIGNAL(triggered()), project, SLOT(saveAs()));
        connect(ui->actionCopyProFileTo,    SIGNAL(triggered()), project, SLOT(forKojnevAlexandrNikolayevich()));
        connect(ui->actionLoadVersionThree, SIGNAL(triggered()), project, SLOT(forDeminValeriyNikolayevich()));
    }
    {
        connect(project, SIGNAL(wasReplaced(QString)), SLOT(setWindowTitle(QString)));
        connect(project, SIGNAL(wasClosed()),          SLOT(restoreWindowTitle()));
        connect(project, SIGNAL(beginReading()),       SLOT(beginWaiting()));
        connect(project, SIGNAL(endReading()),         SLOT(endWaiting()));
    }
}

#include "YesNoMessage.h"
void MainWindow::tryReloadProject()
{
    YesNoMessage::proxyAction(
        this,
        ui->actionAskAboutDanger->isChecked(),
        tr("reload this project?"),
        [this](){project->reload();}
    );
}

void MainWindow::tryCloseProject()
{
    YesNoMessage::proxyAction(
        this,
        ui->actionAskAboutDanger->isChecked(),
        tr("close this project?"),
        [this](){project->close();}
    );
}

void MainWindow::tryClearWindows()
{    
    YesNoMessage::proxyAction(
        this,
        ui->actionAskAboutDanger->isChecked(),
        tr("close all windows?"),
        [this](){groups->clearActiveGroup();}
    );
}

void MainWindow::tryClearGroups()
{
    YesNoMessage::proxyAction(
        this,
        ui->actionAskAboutDanger->isChecked(),
        tr("close all groups?"),
        [this](){groups->closeGroups();}
    );
}

void MainWindow::beginWaiting()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setEnabled(false);
}

void MainWindow::endWaiting()
{
    setEnabled(true);
    QApplication::restoreOverrideCursor();
}

void MainWindow::createSamplesProxyActions()
{
    connect(ui->actionShowSamplesManager, SIGNAL(triggered()), SLOT(showSamplesProxyView()));
    connect(groups, SIGNAL(hasGroups(bool)), ui->actionShowSamplesManager, SLOT(setEnabled(bool)));
}

#include <SamplesProxyView.h>
void MainWindow::showSamplesProxyView()
{
    SamplesProxyView* samplesProxyView = new SamplesProxyView(groups->getGroup()->getSamplesManager(), this);
    samplesProxyView->show();
    samplesProxyView->exec();
    delete samplesProxyView;
}

void MainWindow::retranslate()
{
    ui->retranslateUi(this);
    groupSettings->retranslate();
    plotSettings->retranslate();
    groups->retranslate();
}

void MainWindow::restoreWindowTitle()
{
    setWindowTitle(tr("Rragraph - the lightweight plotter"));
}

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
    ui->menuProject->addAction(ui->actionCopyProFileTo);
    ui->menuProject->addAction(ui->actionLoadVersionThree);
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
    saveSettings();
    return QMainWindow::closeEvent(event);
}

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
        groups->processArgs(args);
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
