#include "SamplesViewer.h"
#include "ui_SamplesViewer.h"
#include "Samples.h"
SamplesViewer::SamplesViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SamplesViewer)
{
    ui->setupUi(this);
    connect(ui->loadFile, SIGNAL(clicked()), SLOT(loadFile()));

    samples = new Samples(this);
    connect(samples, SIGNAL(haveBeenLoaded()), SLOT(haveBeenLoaded()));


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
    int n = samples->count() ? samples->getColumns(0).size() : 0;
    for(int j = 0; j < n; ++j){
        QString res;
        for(int i = 0; i < samples->count(); ++i){
            res.append(QString("%1 ").arg(samples->getColumns(i)[j]));
        }
        ui->samples->append(res);
    }
}

