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

CurvesManagerView::~CurvesManagerView()
{
    saveSettings();
    delete ui;
}

#include <QSettings>
void CurvesManagerView::saveSettings()
{
    QSettings("appSettings.ini", QSettings::IniFormat).setValue(
        "widgets/CurvesManagerView",
         saveGeometry()
    );
}

void CurvesManagerView::restoreSettings()
{
    restoreGeometry(
        QSettings("appSettings.ini", QSettings::IniFormat).value(
            "widgets/CurvesManagerView"
        ).toByteArray()
    );

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

#include <SamplesManagerView.h>
void CurvesManagerView::createSamplesManagerView()
{
    samplesManagerView = new SamplesManagerView(this);
    ui->samplesLayout->addWidget(samplesManagerView);
    samplesManagerView->setSamplesManager(samplesManager);
    connect(samplesManagerView, SIGNAL(wasActivated(int)), SLOT(setCurvesToFiller(int)));
    connect(samplesManagerView, SIGNAL(wasActivated(int)), SLOT(setSamplesPathToWindowTitle(int)));
    connect(samplesManagerView, SIGNAL(wasCleaned()), SLOT(setRawWindowTitle()));
    connect(samplesManagerView, SIGNAL(wasCleaned()), SLOT(curvesFillerToNullData()));
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

void CurvesManagerView::curvesFillerToNullData()
{
    curvesFiller->setCurves(nullptr);
    curvesSettings->setCurves(nullptr);
}
