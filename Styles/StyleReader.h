#ifndef STYLEREADER_H
#define STYLEREADER_H

class QwtPlotCurve;
class QPen;
class QString;
class QwtSymbol;
class StyleCurve;

#include "Item/Item.h"

class StyleReader
{
public:
    static Item plotStyle(const QString& styleName);
    static QPen pen(const QString& styleName);
    static QPen pen(Item* line);
    static QwtSymbol* symbol(const QString& styleName);
    static QwtSymbol* symbol(Item* symbol);
    static void setMarkerStep(int begin, int step, QwtPlotCurve* curve = 0);
    static void fill(const QString& styleName, StyleCurve* style);
};

#endif // STYLEREADER_H
