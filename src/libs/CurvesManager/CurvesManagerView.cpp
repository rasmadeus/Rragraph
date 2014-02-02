#include "CurvesManagerView.h"
#include "ui_CurvesManagerView.h"

#include <SamplesManagerView.h>
#include "CurvesFiller.h"
#include "CurvesSettings.h"
#include <SamplesManager.h>
CurvesManagerView::CurvesManagerView(SamplesManager* samplesManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurvesManagerView),
    curvesManager(nullptr),
    samplesManager(samplesManager)
{
    ui->setupUi(this);

    curvesFiller = new CurvesFiller(this);
    ui->curvesFillerLayout->addWidget(curvesFiller);

    curvesSettings = new CurvesSettings(this);
    ui->curvesSettingsLayout->addWidget(curvesSettings);
    connect(curvesFiller, SIGNAL(dataWasSetted()), curvesSettings, SLOT(resetView()));

    samplesManagerView = new SamplesManagerView(this);
    ui->samplesLayout->addWidget(samplesManagerView);
    samplesManagerView->setSamplesManager(samplesManager);
    connect(samplesManagerView, SIGNAL(wasActivated(int)), SLOT(setCurvesToFiller(int)));
    connect(samplesManagerView, SIGNAL(wasActivated(int)), SLOT(setSamplesPathToWindowTitle(int)));
    connect(samplesManagerView, SIGNAL(wasCleaned()), SLOT(setRawWindowTitle()));

    connect(samplesManager, SIGNAL(haveBeenLoaded(int)), SLOT(updateCurvesToFiller(int)));
}

CurvesManagerView::~CurvesManagerView()
{
    delete ui;
}

#include "CurvesManager.h"
void CurvesManagerView::setCurvesManager(CurvesManager* curvesManager)
{
    {
        this->curvesManager = curvesManager;
    }
    {
        int activeRow = samplesManagerView->getActiveRow();
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
