#include "CurvesManagerView.h"
#include "ui_CurvesManagerView.h"

#include <SamplesManagerView.h>
#include "CurvesFiller.h"
#include "CurvesSettings.h"
CurvesManagerView::CurvesManagerView(QWidget *parent) :
    QWidget(parent),
    curvesManager(nullptr),
    ui(new Ui::CurvesManagerView)
{
    ui->setupUi(this);

    curvesFiller = new CurvesFiller(this);
    ui->curvesFillerLayout->addWidget(curvesFiller);

    curvesSettings = new CurvesSettings(this);
    ui->curvesSettingsLayout->addWidget(curvesSettings);
    connect(curvesFiller, SIGNAL(dataWasSetted()), curvesSettings, SLOT(resetView()));

    samplesManagerView = new SamplesManagerView(this);
    ui->samplesLayout->addWidget(samplesManagerView);
    connect(samplesManagerView, SIGNAL(wasActivated(int)), SLOT(setCurvesToFiller(int)));
}

CurvesManagerView::~CurvesManagerView()
{
    delete ui;
}

#include "CurvesManager.h"
void CurvesManagerView::setCurvesManager(CurvesManager* curvesManager)
{
    this->curvesManager = curvesManager;
    samplesManagerView->setSamplesManager(curvesManager->getSamplesManager());
}

#include <SamplesManager.h>
void CurvesManagerView::setCurvesToFiller(int i)
{
    Curves* curves = curvesManager->getCurves(i);
    curvesFiller->setCurves(curves);
    curvesSettings->setCurves(curves);
    emit wasChoosen(curvesManager->getSamplesManager()->getSamples(i));
}
