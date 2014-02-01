#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Group;
class PlotsGroups;

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
    Ui::MainWindow *ui;
    PlotsGroups* plotsGroups;
};

#endif // MAINWINDOW_H
