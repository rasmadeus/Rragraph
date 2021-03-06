#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Group;
class Groups;
class Project;
class RecentlyProjectPaths;
class Translator;
class GroupSettings;
class PlotSettings;

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void processArgs(const QStringList& args);
protected:
    void closeEvent(QCloseEvent* event);
    void dropEvent(QDropEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
private slots:
    void setActiveActionOfTilingMenu(Group* plots);
    void showSamplesProxyView();
    void restoreWindowTitle();
    void fillProjectMenu();
    void showAbout();
    void retranslate();
    void beginWaiting();
    void endWaiting();
    void tryReloadProject();
    void tryCloseProject();
    void tryClearWindows();
    void tryClearGroups();
private:
    void restoreVisibilityActionsState();
    void restoreSettings();
    void saveSettings();
    void createPlotsGroups();
    void routePlotsMenu();
    void createPlotsTilingMenu();
    void createPlotSettingsView();
    void createSamplesProxyActions();
    void createProject();
    void createRecentlyProjectPaths();
    void initAbout();
    void createTranslator();
    Ui::MainWindow *ui;
    Groups* groups;
    Project* project;
    RecentlyProjectPaths* recentlyProjectPaths;
    Translator* translator;
    GroupSettings* groupSettings;
    PlotSettings* plotSettings;
};

#endif // MAINWINDOW_H
