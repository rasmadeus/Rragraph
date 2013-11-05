#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MdiArea;
class Files;
class HeadersView;
class PlotSettingsView;
class Project;

#include <QMainWindow>
#include <QActionGroup>

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
    void closeEvent(QCloseEvent* evt);
private slots:
    void fillProjectMenu();
    void addLastProjectPaths();
    void localeWasChanged();
private:
    void dragEnterEvent(QDragEnterEvent* evt);
    void dropEvent(QDropEvent* evt);
    Ui::MainWindow *ui;
    Files* files;
    HeadersView* headersView;
    MdiArea* mdiArea;
    PlotSettingsView* plotSettings;
    Project* project;
    QActionGroup* lastProjectPaths;
    QActionGroup* tileBehavior;
};

#endif // MAINWINDOW_H
