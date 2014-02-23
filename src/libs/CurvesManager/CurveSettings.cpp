#include "CurveSettings.h"
#include "ui_CurveSettings.h"

CurveSettings::CurveSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurveSettings),
    curve(nullptr)
{
    ui->setupUi(this);
    fillSymbol();
    ui->sample->installEventFilter(this);
    connect(ui->color, SIGNAL(clicked()), SLOT(setCurveColor()));
    connect(ui->width, SIGNAL(valueChanged(int)), SLOT(setCurveWidth(int)));
    connect(ui->curve, SIGNAL(clicked(bool)), SLOT(setCurveVisible(bool)));
    connect(ui->symbolStyle, SIGNAL(activated(int)), SLOT(setSymbolStyle(int)));
    connect(ui->dashPattern, SIGNAL(textChanged(QString)), SLOT(setCurveDashPattern(QString)));
    connect(ui->addendX, SIGNAL(valueChanged(double)), SLOT(setAddendX(double)));
    connect(ui->addendY, SIGNAL(valueChanged(double)), SLOT(setAddendY(double)));
    connect(ui->multY, SIGNAL(valueChanged(double)), SLOT(setMultY(double)));
    setDataFromCurve();    
}

void CurveSettings::retranslate()
{
    {
        ui->retranslateUi(this);
    }
    {
        ui->symbolStyle->setItemText(0, tr("No symbol"));
        ui->symbolStyle->setItemText(1, tr("Ellipse"));
        ui->symbolStyle->setItemText(2, tr("Rect"));
        ui->symbolStyle->setItemText(3, tr("Diamond"));
        ui->symbolStyle->setItemText(4, tr("Triangle"));
        ui->symbolStyle->setItemText(5, tr("DTriangle"));
        ui->symbolStyle->setItemText(6, tr("UTriangle"));
        ui->symbolStyle->setItemText(7, tr("LTriangle"));
        ui->symbolStyle->setItemText(8, tr("RTriangle"));
        ui->symbolStyle->setItemText(9, tr("Cross"));
        ui->symbolStyle->setItemText(10, tr("XCross"));
        ui->symbolStyle->setItemText(11, tr("HLine"));
        ui->symbolStyle->setItemText(12, tr("VLine"));
        ui->symbolStyle->setItemText(13, tr("Star1"));
        ui->symbolStyle->setItemText(14, tr("Star2"));
    }
}


#include <qwt_symbol.h>
void CurveSettings::fillSymbol()
{
    ui->symbolStyle->addItem(tr("No symbol"), QwtSymbol::NoSymbol);
    ui->symbolStyle->addItem(tr("Ellipse"),   QwtSymbol::Ellipse);
    ui->symbolStyle->addItem(tr("Rect"),      QwtSymbol::Rect);
    ui->symbolStyle->addItem(tr("Diamond"),   QwtSymbol::Diamond);
    ui->symbolStyle->addItem(tr("Triangle"),  QwtSymbol::Triangle);
    ui->symbolStyle->addItem(tr("DTriangle"), QwtSymbol::DTriangle);
    ui->symbolStyle->addItem(tr("UTriangle"), QwtSymbol::UTriangle);
    ui->symbolStyle->addItem(tr("LTriangle"), QwtSymbol::LTriangle);
    ui->symbolStyle->addItem(tr("RTriangle"), QwtSymbol::RTriangle);
    ui->symbolStyle->addItem(tr("Cross"),     QwtSymbol::Cross);
    ui->symbolStyle->addItem(tr("XCross"),    QwtSymbol::XCross);
    ui->symbolStyle->addItem(tr("HLine"),     QwtSymbol::HLine);
    ui->symbolStyle->addItem(tr("VLine"),     QwtSymbol::VLine);
    ui->symbolStyle->addItem(tr("Star1"),     QwtSymbol::Star1);
    ui->symbolStyle->addItem(tr("Star2"),     QwtSymbol::Star2);
}

#include <Plot.h>
#include <Curve.h>
#include "Curves.h"
void CurveSettings::setSymbolStyle(int i)
{
    curve->setSymbolStyle(ui->symbolStyle->itemData(i).toInt());
    update();
    curves->getOwner()->replot();
}

CurveSettings::~CurveSettings()
{
    delete ui;
}

void CurveSettings::setCurve(Curves* curves, Curve* curve)
{
    this->curve = curve;
    this->curves = curves;
    setDataFromCurve();
}

void CurveSettings::setDataFromCurve()
{
    setEnabled(curve);
    if(isEnabled()){
        restore();
    }
}

void CurveSettings::restore()
{
    {
        ui->curve->setChecked(curve->isVisible());
    }
    {
        ui->dashPattern->setText(Curve::getDashPatternFromPen(curve->pen()));
    }
    {
        QPen pen = curve->pen();
        ui->width->setValue(pen.width());
    }
    {
        ui->addendX->setValue(curve->getAddendX());
        ui->addendY->setValue(curve->getAddendY());
        ui->multY->setValue(curve->getMultY());
    }
    {
        int iSymbolStyle = curve->getSymbolStyle();
        for(int i = 0; i < ui->symbolStyle->count(); ++i){
            int itemData = ui->symbolStyle->itemData(i).toInt();
            if(itemData == iSymbolStyle){
                ui->symbolStyle->setCurrentIndex(i);
                break;
            }
        }
    }
}

#include <QColorDialog>
void CurveSettings::setCurveColor()
{
    QPen pen = curve->pen();
    QColor color = QColorDialog::getColor(pen.color(), this, tr("Curve color"));
    if(color.isValid()){
        pen.setColor(color);
        curve->setPen(pen);
        curves->getOwner()->replot();
    }
}

void CurveSettings::setCurveWidth(int width)
{
    QPen pen = curve->pen();
    pen.setWidth(width);
    curve->setPen(pen);
    update();
    curves->getOwner()->replot();
}

#include <QPainter>
bool CurveSettings::eventFilter(QObject* obj, QEvent* evt)
{
    if(curve && evt->type() == QEvent::Paint){
        QPainter painter(ui->sample);
        painter.setPen(curve->pen());
        {
            QRect rect = ui->sample->rect();
            painter.drawLine(rect.left(),  rect.center().y(), rect.right(), rect.center().y());
            if(curve->symbol()){
                curve->symbol()->drawSymbol(&painter, rect.center());
            }
        }
    }
    return QWidget::eventFilter(obj, evt);
}

void CurveSettings::setCurveVisible(bool clicked)
{
    curve->setVisible(clicked);
    if(!clicked){
        curve->detach();
    }
    else{
        curve->attach(curves->getOwner());
    }
    curves->getOwner()->replot();
    emit visibilityCurveChanged();
}

void CurveSettings::setCurveDashPattern(const QString& dashPattern)
{
    QPen pen = curve->pen();
    curve->setPen(Curve::fillPenWithDashPattern(pen, dashPattern));
    curves->getOwner()->replot();
    update();
}

void CurveSettings::setAddendX(double addend)
{
    curve->setAddendX(addend);
    curves->resamples();
}

void CurveSettings::setAddendY(double addend)
{
    curve->setAddendY(addend);
    curves->resamples();
}

void CurveSettings::setMultY(double mult)
{
    curve->setMultY(mult);
    curves->resamples();
}
