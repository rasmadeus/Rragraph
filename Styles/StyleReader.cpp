#include "StyleReader.h"

#include "../qwt-6.0.1/qwt_plot_curve.h"

#include "Item/Item.h"

Item StyleReader::plotStyle(const QString& styleName)
{
    Item item(Item::PLOT_STYLE);
    item.restore("Styles/" + Item::getCaption(Item::ROOT_PLOT) + "/" + styleName);
    return item;
}

QPen StyleReader::pen(const QString& styleName)
{

    Item plotCurve(Item::CURVE_NAME);
    plotCurve.restore("Styles/" + Item::getCaption(Item::ROOT_CURVE) + "/" + styleName);
    QPen pen  = StyleReader::pen(plotCurve.find(Item::CURVE_LINE));
    return pen;
}

QPen StyleReader::pen(Item* line)
{
    if(!line) return QPen();

    QVector<Item*> lineParams = line->findLineParams();

    QPen pen;
    //Set color.
    if(lineParams[0]){
        pen.setColor(lineParams[0]->getValue().value<QColor>());
    }
    //Set pen width.
    pen.setWidth(lineParams[3] ? lineParams[3]->getValue().toInt() : 1);
    //Set dash pattern (if space is not null).
    int space = lineParams[2] ? lineParams[2]->getValue().toInt() : 0;
    if(space && lineParams[1]){
        pen.setDashPattern(QVector<qreal>() << lineParams[1]->getValue().toInt() << space);
    }
    //Return result.
    return pen;
}

#include "../qwt-6.0.1/qwt_symbol.h"
QwtSymbol* StyleReader::symbol(const QString& styleName)
{
    Item plotCurve(Item::CURVE_NAME);
    plotCurve.restore("Styles/" + Item::getCaption(Item::ROOT_CURVE) + "/" + styleName);
    return StyleReader::symbol(plotCurve.find(Item::CURVE_MARKER));
}



QwtSymbol* StyleReader::symbol(Item *symbol)
{
    QwtSymbol* result = new QwtSymbol;

    if(!symbol) return result;

    Item* sizeMarker  = symbol->find(Item::CURVE_MARKER_SIZE);
    int size = sizeMarker ? sizeMarker->getValue().toInt() : 0;
    result->setSize(size);
    if(!size) return result;

    Item* colorMarker = symbol->find(Item::CURVE_MARKER_COLOR);
    if(colorMarker){
        QPen pen = result->pen();
        QColor color = colorMarker->getValue().value<QColor>();
        pen.setColor(color);
        result->setBrush(QBrush(color));
        result->setPen(pen);
    }

    Item* styleMarker = symbol->find(Item::CURVE_MARKER_TYPE);
    if(styleMarker)
        result->setStyle((QwtSymbol::Style)styleMarker->getValue().toInt());

    return result;
}

void StyleReader::setMarkerStep(int begin, int step, QwtPlotCurve *curve)
{
    if(!curve) return;
    curve->setBeginMarkerPoint(begin);
    curve->setMarkerStep(step <= 0 ? 1 : step);
}

#include "StylesCurve.h"
void StyleReader::fill(const QString& styleName, StyleCurve *style)
{
    Item plotCurve(Item::CURVE_NAME);
    plotCurve.restore("Styles/" + Item::getCaption(Item::ROOT_CURVE) + "/" + styleName);
    style->symbol = StyleReader::symbol(plotCurve.find(Item::CURVE_MARKER));
    style->pen = StyleReader::pen(plotCurve.find(Item::CURVE_LINE));

    Item* marker = plotCurve.find(Item::CURVE_MARKER);
    if(marker){
        Item* begin = marker->find(Item::CURVE_MARKER_BEGIN_POINT);
        Item* step = marker->find(Item::CURVE_MARKER_STEP);
        if(begin && step){
            style->begin = begin->getValue().toInt();
            style->step = step->getValue().toInt();
        }
    }
}

