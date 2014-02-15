#include "CurvesSettings.h"
#include "ui_CurvesSettings.h"

#include "CurveSettings.h"
#include "CurvesModel.h"
CurvesSettings::CurvesSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurvesSettings)
{
    ui->setupUi(this);
    curveSettings = new CurveSettings(this);
    ui->curveSettingsLayout->addWidget(curveSettings);
    curvesModel = new CurvesModel(ui->curvesList);
    ui->curvesList->setModel(curvesModel);
    connect(ui->curvesList, SIGNAL(pressed(QModelIndex)), curvesModel, SLOT(setActiveRow(QModelIndex)));
    connect(ui->curvesList, SIGNAL(pressed(QModelIndex)), SLOT(setCurveSettings()));
    connect(curveSettings, SIGNAL(visibilityCurveChanged()), SIGNAL(visibilityCurveChanged()));
}

CurvesSettings::~CurvesSettings()
{
    delete ui;
}

void CurvesSettings::setCurveSettings()
{
    curveSettings->setCurve(curvesModel->getCurves(), curvesModel->getCurve());
}

void CurvesSettings::setCurves(Curves* curves)
{
    curvesModel->setCurves(curves);
    if(!curves){
        curveSettings->setCurve(nullptr, nullptr);
    }
}

void CurvesSettings::resetView()
{
    curvesModel->resetModel();
}
