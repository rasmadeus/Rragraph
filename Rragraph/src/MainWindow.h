#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MdiArea;
class Files;
class HeadersView;
class PlotSettingsView;
class Project;

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;
    Files* files;
    HeadersView* headersView;
    MdiArea* mdiArea;
    PlotSettingsView* plotSettings;
    Project* project;
protected:
    void closeEvent(QCloseEvent* evt);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
