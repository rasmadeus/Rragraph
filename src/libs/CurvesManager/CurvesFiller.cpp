#include "CurvesFiller.h"
#include "ui_CurvesFiller.h"

#include "CurvesFillerModel.h"
CurvesFiller::CurvesFiller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurvesFiller)
{
    ui->setupUi(this);
    model = new CurvesFillerModel(this);
    ui->filler->setModel(model);
    connect(ui->filler, SIGNAL(clicked(QModelIndex)), SLOT(setModelData(QModelIndex)));
    connect(model, SIGNAL(dataWasSetted()), SIGNAL(dataWasSetted()));
}

CurvesFiller::~CurvesFiller()
{
    delete ui;
}

void CurvesFiller::setCurves(Curves* curves)
{
    model->setCurves(curves);
    ui->filler->resizeColumnsToContents();
    ui->filler->resizeRowsToContents();
}

void CurvesFiller::setModelData(const QModelIndex& index)
{
    model->setData(index);
}
