#include "CurvesManagerView.h"
#include "ui_CurvesManagerView.h"

#include <SamplesManager.h>
CurvesManagerView::CurvesManagerView(SamplesManager* samplesManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurvesManagerView),
    curvesManager(nullptr),
    samplesManager(samplesManager)
{
    ui->setupUi(this);
    createCurvesFiller();
    createCurvesSettings();
    createSamplesManagerView();
    connect(samplesManager, SIGNAL(haveBeenLoaded(int)), SLOT(updateCurvesToFiller(int)));
    restoreSettings();
}

#include "CurvesFiller.h"
void CurvesManagerView::createCurvesFiller()
{
    curvesFiller = new CurvesFiller(this);
    ui->curvesFillerLayout->addWidget(curvesFiller);
}

#include "CurvesSettings.h"
void CurvesManagerView::createCurvesSettings()
{
    curvesSettings = new CurvesSettings(this);
    ui->curvesSettingsLayout->addWidget(curvesSettings);
    connect(curvesFiller, SIGNAL(dataWasSetted()), curvesSettings, SLOT(resetView()));
    connect(curvesSettings, SIGNAL(visibilityCurveChanged()), curvesFiller, SLOT(resetModel()));
}


CurvesManagerView::~CurvesManagerView()
{
    saveSettings();
    delete ui;
}

#include <Settings.h>
void CurvesManagerView::saveSettings()
{
    Settings::obj()->set("widgets/CurvesManagerView", saveGeometry());
}

void CurvesManagerView::restoreSettings()
{
    restoreGeometry(Settings::obj()->get("widgets/CurvesManagerView").toByteArray());
}

#include <SamplesManagerView.h>
void CurvesManagerView::createSamplesManagerView()
{
    samplesManagerView = new SamplesManagerView(this);
    ui->samplesLayout->addWidget(samplesManagerView);
    samplesManagerView->setSamplesManager(samplesManager);
    connect(samplesManagerView, SIGNAL(wasActivated(int)), SLOT(setCurvesToFiller(int)));
    connect(samplesManagerView, SIGNAL(wasActivated(int)), SLOT(setSamplesPathToWindowTitle(int)));
    connect(samplesManagerView, SIGNAL(wasCleaned()),      SLOT(setRawWindowTitle()));
    connect(samplesManagerView, SIGNAL(wasCleaned()),      SLOT(curvesFillerToNullData()));
}

#include "CurvesManager.h"
void CurvesManagerView::setCurvesManager(CurvesManager* curvesManager)
{
    {
        this->curvesManager = curvesManager;
    }
    {
        curvesSettings->reset();
    }
    {
        const int activeRow = samplesManagerView->getActiveRow();
        if(activeRow != -1){
            setCurvesToFiller(activeRow);
        }
    }
}

#include <SamplesManager.h>
void CurvesManagerView::setCurvesToFiller(int i)
{
    Curves* curves = curvesManager->getCurves(i);
    curvesFiller->setCurves(curves);
    curvesSettings->setCurves(curves);
    emit wasChoosen(curvesManager->getSamplesManager()->getSamples(i));
}

#include <Samples.h>
void CurvesManagerView::setSamplesPathToWindowTitle(int i)
{
    setWindowTitle(samplesManager->getSamples(i)->getPathToSrc());
}

void CurvesManagerView::setRawWindowTitle()
{
    setWindowTitle(tr("Curves manager"));
    curvesFiller->setCurves(nullptr);
}

void CurvesManagerView::updateCurvesToFiller(int i)
{
    if(i == samplesManagerView->getActiveRow()){
        setCurvesToFiller(i);
    }
}

void CurvesManagerView::curvesFillerToNullData()
{
    curvesFiller->setCurves(nullptr);
    curvesSettings->setCurves(nullptr);
}

void CurvesManagerView::retranslate()
{
    ui->retranslateUi(this);
    curvesSettings->retranslate();
    samplesManagerView->retranslate();
}

void CurvesManagerView::setInitialLoadingPath(const QString& path)
{
    samplesManagerView->setInitialLoadingPath(path);
}
