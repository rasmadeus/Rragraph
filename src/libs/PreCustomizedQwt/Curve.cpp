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

void Curve::setStep(int step)
{
    this->step = step;
}

int Curve::getStep() const
{
    return step;
}

void Curve::setAddendY(double addend)
{
    addendY = addend;
}

double Curve::getAddendY() const
{
    return addendY;
}

double Curve::getAddendX() const
{
    return addendX;
}

void Curve::setAddendX(double addend)
{
    addendX = addend;
}

void Curve::setMultY(double mult)
{
    multY = mult;
}

double Curve::getMultY() const{
    return multY;
}

int Curve::getSymbolStyle() const
{
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

void Curve::setPen(const QPen& pen)
{
    QwtPlotCurve::setPen(pen);
    setSymbolStyle(symbolStyle);
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

QPen Curve::fillPenWithDashPattern(const QPen& src, const QString& dashes)
{
    QPen pen;
    pen.setWidth(src.width());
    pen.setColor(src.color());
    if(dashes.isEmpty()){
        return pen;
    }
    QVector<double> dashPattern;
    foreach(const QString& dash, dashes.simplified().split(" ")){
        const double dashValue = dash.toDouble();
        dashPattern << dashValue;
    }
    if(dashPattern.size() % 2  == 1){
        dashPattern << 1;
    }
    pen.setDashPattern(dashPattern);
    return pen;
}

QString Curve::getDashPatternFromPen(const QPen& pen)
{
    QString dashes;
    foreach(double dashValue, pen.dashPattern()){
        dashes.append(QString("%1 ").arg(dashValue));
    }
    return dashes;
}

#include <QJsonObject>
void serializeDashPattern(QJsonObject& curveSettings, const QPen& pen)
{
    const QString dashPattern = Curve::getDashPatternFromPen(pen);
    if(!dashPattern.isEmpty()){
        curveSettings.insert("dashPattern", dashPattern);
    }
}

#include <QJsonArray>
QJsonObject Curve::serialize() const
{
    QJsonObject curveSettings;
    curveSettings.insert("isVisible", isVisible());
    curveSettings.insert("symbolStyle", QJsonValue::fromVariant(symbolStyle));
    curveSettings.insert("addendX", QJsonValue::fromVariant(addendX));
    curveSettings.insert("addendY", QJsonValue::fromVariant(addendY));
    curveSettings.insert("multY", QJsonValue::fromVariant(multY));
    curveSettings.insert("step", QJsonValue::fromVariant(step));
    curveSettings.insert("penColor", QJsonValue::fromVariant(pen().color()));
    curveSettings.insert("penWidth", QJsonValue::fromVariant(pen().width()));
    serializeDashPattern(curveSettings, pen());
    return curveSettings;
}

QPen restorePen(const QJsonObject& curveSettings)
{
    QPen pen;
    pen.setWidth(curveSettings.value("penWidth").toVariant().toInt());
    pen.setColor(curveSettings.value("penColor").toVariant().value<QColor>());
    return Curve::fillPenWithDashPattern(pen, curveSettings.value("dashPattern").toString());
}

void Curve::restore(const QJsonObject& curveSettings)
{
    setVisible(curveSettings.value("isVisible").toBool());
    setSymbolStyle(curveSettings.value("symbolStyle").toVariant().toInt());
    setAddendX(curveSettings.value("addendX").toDouble(0));
    setAddendY(curveSettings.value("addendY").toDouble(0));
    setMultY(curveSettings.value("multY").toDouble(1));
    setStep(curveSettings.value("step").toVariant().toInt());
    setPen(restorePen(curveSettings));
}
