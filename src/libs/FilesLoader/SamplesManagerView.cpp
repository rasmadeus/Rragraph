#include "SamplesManagerView.h"
#include "ui_SamplesManagerView.h"

Path SamplesManagerView::samplesLoadingPath("appSettings.ini","paths/samplesLoadingPath");

#include "SamplesManagerModel.h"
SamplesManagerView::SamplesManagerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SamplesManagerView)
{
    ui->setupUi(this);
    samplesManagerModel = new SamplesManagerModel(this);
    ui->samplesList->setModel(samplesManagerModel);
    connect(ui->insertNewSamples, SIGNAL(clicked()), SLOT(insertNewSamples()));
    connect(ui->removeSamples, SIGNAL(clicked()), SLOT(removeSamples()));
    connect(ui->replaceSamples, SIGNAL(clicked()), SLOT(replaceSamples()));
    connect(ui->samplesList, SIGNAL(pressed(QModelIndex)), samplesManagerModel, SLOT(setActiveRow(QModelIndex)));
    connect(samplesManagerModel, SIGNAL(wasActivated(int)), SIGNAL(wasActivated(int)));
    connect(samplesManagerModel, SIGNAL(wasCleaned()), SIGNAL(wasCleaned()));
}

SamplesManagerView::~SamplesManagerView()
{
    delete ui;
}

void SamplesManagerView::setSamplesManager(SamplesManager* samplesManager)
{
    samplesManagerModel->setSamplesManager(samplesManager);
}

#include <QFileDialog>
void SamplesManagerView::insertNewSamples()
{
    foreach(const QString& path, samplesLoadingPath.getOpenFileNames(this, tr("Load data files"))){
        samplesManagerModel->append(path);
    }
}

void SamplesManagerView::removeSamples()
{
    samplesManagerModel->remove();
}

void SamplesManagerView::replaceSamples()
{
    if(samplesManagerModel->rowCount()){
        QString path = samplesLoadingPath.getOpenFileName(this, tr("Replace with"));
        if(!path.isEmpty()){
            samplesManagerModel->replace(path);
        }
    }
}

int SamplesManagerView::getActiveRow() const
{
    return samplesManagerModel->getActiveRow();
}
