#include "SamplesManagerView.h"
#include "ui_SamplesManagerView.h"

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
#include "SamplesManager.h"
void SamplesManagerView::insertNewSamples()
{
    QStringList pathsToSrc = QFileDialog::getOpenFileNames(this, tr("Load files"));
    foreach(const QString& path, pathsToSrc){
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
        samplesManagerModel->replace(QFileDialog::getOpenFileName(this, tr("Load file")));
    }
}

int SamplesManagerView::getActiveRow() const
{
    return samplesManagerModel->getActiveRow();
}
