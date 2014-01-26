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
    setDataFromCurve();    
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

#include <Curve.h>
void CurveSettings::setSymbolStyle(int i)
{
    curve->setSymbolStyle(ui->symbolStyle->itemData(i).toInt());
    update();
}

CurveSettings::~CurveSettings()
{
    delete ui;
}

void CurveSettings::setCurve(Curve* curve)
{
    this->curve = curve;
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
        QPen pen = curve->pen();
        ui->width->setValue(pen.width());
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
    {
        ui->dashPattern->setText(Curve::getDashPatternFromPen(curve->pen()));
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
    }
}

void CurveSettings::setCurveWidth(int width)
{
    QPen pen = curve->pen();
    pen.setWidth(width);
    curve->setPen(pen);
    update();
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
}

void CurveSettings::setCurveDashPattern(const QString& dashPattern)
{
    QPen pen = curve->pen();
    curve->setPen(Curve::fillPenWithDashPattern(pen, dashPattern));
    update();
}