#include "CurvesCustomizer.h"
#include "ui_CurvesCustomizer.h"

#include <CurvesManagerView.h>
CurvesCustomizer::CurvesCustomizer(SamplesManager* samplesManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurvesCustomizer)
{
    ui->setupUi(this);
    curvesManagerView = new CurvesManagerView(samplesManager, this);
    ui->verticalLayout->addWidget(curvesManagerView);
}

CurvesCustomizer::~CurvesCustomizer()
{
    delete ui;
}

CurvesManagerView* CurvesCustomizer::getCurvesManagerView() const
{
    return curvesManagerView;
}
