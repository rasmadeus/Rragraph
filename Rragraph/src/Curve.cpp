#include "Curve.h"

Curve::Curve(const QString& name):
    QwtPlotCurve(name),
    step(10),
    addendY(0),
    addendX(0),
    multY(1),
    symbolStyle(-1)
{    
    setLegendAttribute(QwtPlotCurve::LegendShowLine);
    setLegendAttribute(QwtPlotCurve::LegendShowSymbol);
    setStyle(Lines);
    setPaintAttribute(ClipPolygons);
    setRenderHint(RenderAntialiased);
}

void Curve::setStep(int step){
    this->step = step;
}

int Curve::getStep() const{
    return step;
}

void Curve::setAddendY(double addend){
    addendY = addend;
}

double Curve::getAddendY() const{
    return addendY;
}

double Curve::getAddendX() const{
    return addendX;
}

void Curve::setAddendX(double addend){
    addendX = addend;
}

void Curve::setMultY(double mult){
    multY = mult;
}

double Curve::getMultY() const{
    return multY;
}

int Curve::getSymbolStyle() const{
    return symbolStyle;
}

#include <qwt_symbol.h>
void Curve::setSymbolStyle(int style)
{
    this->symbolStyle = style;
    if(style == -1){
        setSymbol(nullptr);
    }
    else{
        QwtSymbol* symbol = new QwtSymbol(QwtSymbol::Style(style));
        symbol->setColor(pen().color());
        symbol->setBrush(QBrush(pen().color()));
        symbol->setPen(pen());
        symbol->setSize(pen().width() + 5);
        setSymbol(symbol);
    }
}

void Curve::setSamples(const QVector<double>& xData, const QVector<double>& yData)
{
    QVector<double> x;
    QVector<double> y;

    if(addendX){
        std::transform(
            xData.begin(),
            xData.end(),
            std::back_inserter(x),
            [this](double x){return x + addendX;}
        );
    }

    if(addendY || multY != 1){
        std::transform(
            yData.begin(),
            yData.end(),
            std::back_inserter(y),
            [this](double y){return multY * y + addendY;}
        );
    }

    QwtPlotCurve::setSamples(
        x.isEmpty() ? xData : x,
        y.isEmpty() ? yData : y
    );
}

#include <qwt_point_mapper.h>
#include <qwt_painter.h>
#include <qwt_symbol.h>
void Curve::drawSymbols(
    QPainter* painter,
    const QwtSymbol& symbol,
    const QwtScaleMap& xMap,
    const QwtScaleMap& yMap,
    const QRectF& canvasRect,
    int from,
    int to
) const
{
    QwtPointMapper mapper;

    mapper.setFlag(
        QwtPointMapper::RoundPoints,
        QwtPainter::roundingAlignment(painter)
    );

    mapper.setFlag(
        QwtPointMapper::WeedOutPoints,
        testPaintAttribute(QwtPlotCurve::FilterPoints)
    );

    mapper.setBoundingRect(canvasRect);

    const int chunkSize = 500;

    for(int i = from; i <= to; i += chunkSize){
        const int n = qMin(chunkSize, to - i + 1);
        const QPolygonF points = mapper.toPointsF(xMap, yMap, data(), i, i + n - 1);

        QPolygonF samples;
        for(int i = 0; i< points.size(); i += step){
            samples << points[i];
        }

        if(points.size() > 0){
            symbol.drawSymbols(painter, samples);
        }
    }
}

#include <QJsonObject>
void Curve::serialize(QJsonObject& curves) const
{
    QJsonObject curve;
    curve["step"]        = step;
    curve["addendY"]     = addendY;
    curve["addendX"]     = addendX;
    curve["multY"]       = multY;
    curve["symbolStyle"] = symbolStyle;
    curve["penColor"]    = QJsonValue::fromVariant(pen().color());
    curve["penWidth"]    = pen().width();
    curves["curveSettings"] = curve;
}

void Curve::restore(const QJsonObject& curves)
{
    const QJsonObject curve = curves.value("curveSettings").toObject();
    step = curve.value("step").toVariant().toInt();
    addendY = curve.value("addendY").toDouble(0);
    addendX = curve.value("addendX").toDouble(0);
    multY = curve.value("multY").toDouble(1);
    const QColor penColor = curve.value("penColor").toVariant().value<QColor>();
    const int penWidth = curve.value("penWidth").toVariant().toInt();
    QPen pen(penColor);
    pen.setWidth(penWidth);
    setPen(pen);
    setSymbolStyle(curve.value("symbolStyle").toVariant().toInt());
}
