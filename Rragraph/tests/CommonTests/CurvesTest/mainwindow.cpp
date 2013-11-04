#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../../src/Plot.h"
#include <QFile>
#include <QTextStream>
#include <qmath.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plot = new Plot(this);
    setCentralWidget(plot);

    QFile file("test.txt");
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out << "t,c sin cos";
        for(double i = 0; i <= 10; i += 0.01 ){
            out << i << " " << qSin(M_PI * i) << " " << qCos(M_PI * i);
            if(i != 10){
                out << "\n";
            }
        }
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    QFile file("test.txt");
    file.remove();
}
