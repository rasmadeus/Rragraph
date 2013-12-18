#include "SamplesViewer.h"
#include "ui_SamplesViewer.h"
#include "Samples.h"
#include "SamplesManager.h"
#include "SamplesQListModel.h"
SamplesViewer::SamplesViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SamplesViewer)
{
    ui->setupUi(this);
    connect(ui->loadFile, SIGNAL(clicked()), SLOT(loadFile()));

    samples = new Samples(this);
    connect(samples, SIGNAL(haveBeenLoaded()), SLOT(haveBeenLoaded()));

    manager = new SamplesManager(this);
    model = new SamplesQListModel(this);
    model->setSamplesManager(manager);
    ui->listView->setModel(model);
    connect(ui->loadFiles, SIGNAL(clicked()), SLOT(loadFiles()));
    connect(ui->removeFile, SIGNAL(clicked()), SLOT(removeFile()));
}

SamplesViewer::~SamplesViewer()
{
    delete ui;
}

#include <QDebug>
#include <QFileDialog>
void SamplesViewer::loadFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Choose any file"), QString(), tr("Text files(*.txt)"));
    if(!path.isEmpty()){
        samples->load(path);
    }
}

void SamplesViewer::haveBeenLoaded()
{
    ui->samples->append(samples->getPathToSrc());
}

void SamplesViewer::loadFiles()
{
    QStringList paths = QFileDialog::getOpenFileNames(this, tr("Choose any files"), QString(), tr("Text files(*.txt)"));
    qDebug() << paths;
    if(!paths.isEmpty()){
        foreach(const QString& path, paths){
            manager->append(path);
        }
    }
    qDebug() << manager->count();
    qDebug() << model->rowCount(QModelIndex());
}

void SamplesViewer::removeFile()
{
    const int i = ui->listView->currentIndex().row();
    if(i >= 0 && i < manager->count()){
        manager->remove(ui->listView->currentIndex().row());
    }
}
