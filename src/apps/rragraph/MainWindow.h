#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Group;
class Groups;

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
private slots:
    void setActiveActionOfTilingMenu(Group* plots);
private:
    void createPlotsGroups();
    void routePlotsMenu();
    void createPlotsTilingMenu();
    void createPlotSettingsView();
    Ui::MainWindow *ui;
    Groups* plotsGroups;
};

#endif // MAINWINDOW_H
