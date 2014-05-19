#include "SamplesManagerView.h"
#include "ui_SamplesManagerView.h"

Path SamplesManagerView::samplesLoadingPath("paths/samplesLoadingPath");

#include "SamplesManagerModel.h"
SamplesManagerView::SamplesManagerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SamplesManagerView)
{
    ui->setupUi(this);
    createSamplesManagerModel();
    routeManagerActions();
}

void SamplesManagerView::retranslate()
{
    ui->retranslateUi(this);
}

void SamplesManagerView::createSamplesManagerModel()
{
    samplesManagerModel = new SamplesManagerModel(this);
    connect(samplesManagerModel, SIGNAL(wasActivated(int)), SIGNAL(wasActivated(int)));
    connect(samplesManagerModel, SIGNAL(wasCleaned()),      SIGNAL(wasCleaned()));
    connect(samplesManagerModel, SIGNAL(wasCleaned()),      SLOT(disabledChangableActions()));
    connect(samplesManagerModel, SIGNAL(wasActivated(int)), SLOT(enabledChangableActions()));
    ui->samplesList->setModel(samplesManagerModel);
}

void SamplesManagerView::routeManagerActions()
{
    connect(ui->insertNewSamples, SIGNAL(clicked()), SLOT(insertNewSamples()));
    connect(ui->removeSamples,    SIGNAL(clicked()), SLOT(removeSamples()));
    connect(ui->replaceSamples,   SIGNAL(clicked()), SLOT(replaceSamples()));
    connect(ui->samplesList,      SIGNAL(pressed(QModelIndex)), samplesManagerModel, SLOT(setActiveRow(QModelIndex)));
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
    foreach(const QString& path, samplesLoadingPath.getOpenFileNames(this, tr("Load data files"), Path::getTemplate(Path::ALL_FILES))){
        samplesManagerModel->append(path);
    }
}

void SamplesManagerView::removeSamples()
{
    samplesManagerModel->remove();
}

void SamplesManagerView::replaceSamples()
{
    if(samplesLoadingPath.setOpenFileName(this, tr("Replace with"))){
        samplesManagerModel->replace(samplesLoadingPath.getPath());
    }
}

int SamplesManagerView::getActiveRow() const
{
    return samplesManagerModel->getActiveRow();
}

SamplesManager* SamplesManagerView::getSamplesManager() const
{
    return samplesManagerModel->getSamplesManager();
}

void SamplesManagerView::enabledChangableActions()
{
    if(!ui->removeSamples->isEnabled()){
        ui->removeSamples->setEnabled(true);
        ui->replaceSamples->setEnabled(true);
    }
}

void SamplesManagerView::disabledChangableActions()
{
    ui->removeSamples->setEnabled(false);
    ui->replaceSamples->setEnabled(false);
}
