#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Plot.h"
#include "Curve.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plot = new Plot(this);
    curve = new Curve("Sinus");
    QVector<double> x;
    QVector<double> y;
    for(double t = -10; t <= 10; t += 0.1){
        x << t;
        y << 2 * sin(2 * M_PI * 5 * t);
    }
    curve->setSamples(x, y);
    curve->attach(plot);
    setCentralWidget(plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}
