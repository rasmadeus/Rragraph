#include "CurveSettings.h"
#include "ui_CurveSettings.h"

#include <qwt_symbol.h>
CurveSettings::CurveSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurveSettings),
    curve(nullptr),
    curves(nullptr)
{
    ui->setupUi(this);

    ui->symbolType->addItem(tr("Ellipse"),       QwtSymbol::Ellipse);
    ui->symbolType->addItem(tr("Rect"),          QwtSymbol::Rect);
    ui->symbolType->addItem(tr("Diamond"),       QwtSymbol::Diamond);
    ui->symbolType->addItem(tr("Up triangle"),   QwtSymbol::Triangle);
    ui->symbolType->addItem(tr("Down triangle"), QwtSymbol::DTriangle);
    ui->symbolType->addItem(tr("HLine"),         QwtSymbol::HLine);

    connect(ui->width,          SIGNAL(valueChanged(int)),        SLOT(setWidth(int)));
    connect(ui->multY,          SIGNAL(valueChanged(double)),     SLOT(setScale(double)));
    connect(ui->addendX,        SIGNAL(valueChanged(double)),     SLOT(setAddendX(double)));
    connect(ui->addendY,        SIGNAL(valueChanged(double)),     SLOT(setAddendY(double)));
    connect(ui->symbol,         SIGNAL(clicked(bool)),            SLOT(turnSymbol(bool)));
    connect(ui->step,           SIGNAL(valueChanged(int)),        SLOT(setStep(int)));
    connect(ui->symbolType,     SIGNAL(currentIndexChanged(int)), SLOT(setSymbolStyle(int)));
    connect(ui->color,          SIGNAL(clicked()),                SLOT(setColor()));
    connect(ui->setDashPattern, SIGNAL(clicked()),                SLOT(setDushPattern()));
}

CurveSettings::~CurveSettings(){
    delete ui;
}

#include "Curves.h"
#include "Curve.h"
#include <qwt_symbol.h>
void CurveSettings::setModel(Curves* curves, int row)
{
//1.
    this->curves = curves;
    this->row = row;
    curves->ifSetY(row);
    curve = curves->getCurve(row);
//2.
    ui->width->setValue(curve->pen().width());
//3.
    ui->addendX->setValue(curve->getAddendX());
    ui->addendY->setValue(curve->getAddendY());
    ui->multY->setValue(curve->getMultY());
//4.
    ui->step->setValue(curve->getStep());
    const QwtSymbol* symbol = curve->symbol();
    ui->symbol->setChecked(symbol);
    if(symbol){
        ui->symbolType->setCurrentIndex(curve->getSymbolStyle());
    }
//5.
    QString text = Curve::fromPenDashPattern(curve->pen());
    ui->dashPattern->setText(text);
}

void CurveSettings::setDushPattern()
{
    QPen pen = curves->getCurve(row)->pen();
    pen = Curve::fillPenWithDashPattern(pen, ui->dashPattern->text());
    curves->setPen(row, pen);
}

void CurveSettings::setWidth(int width){
    curves->setWidth(row, width);
}

void CurveSettings::localeWasChanged(){
    ui->retranslateUi(this);
    ui->symbolType->setItemText(0, tr("Ellipse"));
    ui->symbolType->setItemText(1, tr("Rect"));
    ui->symbolType->setItemText(2, tr("Diamond"));
    ui->symbolType->setItemText(3, tr("Up triangle"));
    ui->symbolType->setItemText(4, tr("Down triangle"));
    ui->symbolType->setItemText(5, tr("HLine"));
}

void CurveSettings::setScale(double scale){
    curves->setScale(row, scale);
}

void CurveSettings::setAddendX(double add){
    curves->setAbscissAddend(row, add);
}

void CurveSettings::setAddendY(double add){
    curves->setOrdinateAddend(row, add);
}

void CurveSettings::setStep(int step){
    curves->setSymbolStep(row, step);
}

void CurveSettings::setSymbolStyle(int i){
    curves->setSymbolStyle(row, ui->symbolType->itemData(i).toInt());
}

void CurveSettings::turnSymbol(bool on)
{
    const int i = ui->symbolType->currentIndex();
    const int type = ui->symbolType->itemData(i).toInt();
    curves->setSymbolStyle(row, on ?  type : -1);
}

#include <QColorDialog>
void CurveSettings::setColor()
{
    setVisible(false);
    QColor color = QColorDialog::getColor(
        curve->pen().color(),
        this,
        tr("Set the curve color")
    );
    if(color.isValid()){
        curves->setColor(row, color);
    }
    setVisible(true);
}
