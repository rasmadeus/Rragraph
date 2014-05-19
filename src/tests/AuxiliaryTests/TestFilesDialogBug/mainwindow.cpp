#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->testerWithParent, SIGNAL(clicked()), SLOT(testWithParent()));
    connect(ui->testerWithoutParent, SIGNAL(clicked()), SLOT(testWithoutParent()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QFileDialog>
void MainWindow::testWithParent()
{
    QFileDialog::getOpenFileName(this);
}

//Условия: windows xp 32 b, Qt 5.0.1.
//Проблема: если отсутствует parent у QFileDialog, тогда
//после exec() диалога, главное окно сворачивается.
void MainWindow::testWithoutParent()
{
    QFileDialog::getOpenFileName();
}
