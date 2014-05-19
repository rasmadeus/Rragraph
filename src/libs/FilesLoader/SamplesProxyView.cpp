#include "SamplesProxyView.h"
#include "ui_SamplesProxyView.h"

SamplesProxyView::SamplesProxyView(SamplesManager* samplesManager, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SamplesProxyView)
{
    ui->setupUi(this);
    createSamplesManagerView();
    createSamplesProxyModel();
    routeProxyViewActions();
    customizeProxyView();
    setSamplesManager(samplesManager);
}

#include "SamplesManagerView.h"
void SamplesProxyView::createSamplesManagerView()
{
    samplesManagerView = new SamplesManagerView(this);
    ui->samplesLayout->addWidget(samplesManagerView);
    connect(samplesManagerView, SIGNAL(wasActivated(int)), SLOT(setSamples(int)));
    connect(samplesManagerView, SIGNAL(wasCleaned()),      SLOT(disabledResetGroup()));
    connect(samplesManagerView, SIGNAL(wasActivated(int)), SLOT(checkEnabledResetGroup(int)));
    connect(samplesManagerView, SIGNAL(wasActivated(int)), SLOT(setSamplesPathToWindowTitle(int)));
    connect(samplesManagerView, SIGNAL(wasCleaned()),      SLOT(restoreWindowTitle()));
}

#include "SamplesProxyView.h"
#include "SamplesProxyModel.h"
void SamplesProxyView::createSamplesProxyModel()
{
    samplesProxyModel = new SamplesProxyModel(ui->proxyView);
    connect(ui->addendReset,  SIGNAL(clicked()), samplesProxyModel, SLOT(resetAddend()));
    connect(ui->multReset,    SIGNAL(clicked()), samplesProxyModel, SLOT(resetMult()));
    connect(ui->headersReset, SIGNAL(clicked()), samplesProxyModel, SLOT(resetHeaders()));
}

#include "DoubleDelegate.h"
#include "StringDelegate.h"
void SamplesProxyView::customizeProxyView()
{
    ui->proxyView->setModel(samplesProxyModel);
    ui->proxyView->setItemDelegateForColumn(0, new StringDelegate(ui->proxyView));
    ui->proxyView->setItemDelegateForColumn(1, new DoubleDelegate(ui->proxyView));
    ui->proxyView->setItemDelegateForColumn(2, new DoubleDelegate(ui->proxyView));
}

void SamplesProxyView::routeProxyViewActions()
{
    connect(ui->proxyView, SIGNAL(clicked(QModelIndex)), ui->proxyView, SLOT(edit(QModelIndex)));
}

SamplesProxyView::~SamplesProxyView()
{
    delete ui;
}

#include "SamplesManager.h"
void SamplesProxyView::setSamplesManager(SamplesManager* samplesManager)
{      
    this->samplesManager = samplesManager;
    samplesManagerView->setSamplesManager(samplesManager);
    connect(samplesManager, SIGNAL(haveBeenLoaded(int)), SLOT(updateEnabledResetGroup(int)));
}

void SamplesProxyView::setSamples(int i)
{
    samplesProxyModel->setSamples(samplesManager->getSamples(i));
}

void SamplesProxyView::disabledResetGroup()
{
    setEnabledResetGroup(false);
}

void SamplesProxyView::enabledResetGroup()
{
    setEnabledResetGroup(true);
}

void SamplesProxyView::setEnabledResetGroup(bool on)
{
    ui->addendReset->setEnabled(on);
    ui->multReset->setEnabled(on);
    ui->headersReset->setEnabled(on);
}

#include "Samples.h"
void SamplesProxyView::checkEnabledResetGroup(int i)
{
    setEnabledResetGroup(!samplesManagerView->getSamplesManager()->getSamples(i)->isLoading());
}

void SamplesProxyView::updateEnabledResetGroup(int i)
{
    if(samplesManagerView->getActiveRow() == i){
        enabledResetGroup();
    }
}

void SamplesProxyView::setSamplesPathToWindowTitle(int i)
{
    setWindowTitle(samplesManager->getSamples(i)->getPathToSrc());
}

void SamplesProxyView::restoreWindowTitle()
{
    setWindowTitle(tr("Proxy settings"));
}

void SamplesProxyView::setInitialLoadingPath(const QString& path)
{
    samplesManagerView->setInitialLoadingPath(path);
}
