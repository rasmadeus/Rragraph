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
}

CurvesSettings::~CurvesSettings()
{
    delete ui;
}

void CurvesSettings::setCurveSettings()
{
    curveSettings->setCurve(curvesModel->getCurve());
}

void CurvesSettings::setCurves(Curves* curves)
{
    curvesModel->setCurves(curves);
}

void CurvesSettings::resetView()
{
    curvesModel->resetModel();
}
