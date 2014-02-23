#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Group;
class Groups;
class Project;
class SamplesProxyView;
class RecentlyProjectPaths;
class Translator;

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
private slots:
    void setActiveActionOfTilingMenu(Group* plots);
    void showSamplesProxyView();
    void restoreWindowTitle();
    void fillProjectMenu();
    void showAbout();
    void retranslate();
private:
    void restoreVisibilityActionsState();
    void restoreSettings();
    void saveSettings();
    void createPlotsGroups();
    void routePlotsMenu();
    void createPlotsTilingMenu();
    void createPlotSettingsView();
    void createSamplesManager();
    void createProject();
    void createRecentlyProjectPaths();
    void initAbout();
    void createTranslator();
    Ui::MainWindow *ui;
    Groups* groups;
    SamplesProxyView* samplesProxyView;
    Project* project;
    RecentlyProjectPaths* recentlyProjectPaths;
    Translator* translator;
};

#endif // MAINWINDOW_H
