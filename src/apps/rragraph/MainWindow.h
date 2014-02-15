#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Group;
class Groups;
class SamplesProxyView;

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
protected:
    void closeEvent(QCloseEvent* event);
private slots:
    void setActiveActionOfTilingMenu(Group* plots);
    void showSamplesProxyView();
private:
    void restoreVisibilityActionsState();
    void restoreSettings();
    void saveSettings();
    void createPlotsGroups();
    void routePlotsMenu();
    void createPlotsTilingMenu();
    void createPlotSettingsView();
    void createSamplesManager();
    Ui::MainWindow *ui;
    Groups* plotsGroups;
    SamplesProxyView* samplesProxyView;
};

#endif // MAINWINDOW_H
