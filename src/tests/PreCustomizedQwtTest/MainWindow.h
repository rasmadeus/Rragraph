#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Plot;
class Curve;
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

private:
    Plot* plot;
    Curve* curve;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
