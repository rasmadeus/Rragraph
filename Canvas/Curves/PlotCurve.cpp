#include "PlotCurve.h"
#include <QSettings>
#include "../../qwt-6.0.1/qwt_symbol.h"

QList<PlotCurve*> PlotCurve::plotCurves;

PlotCurve::PlotCurve(QString name) :
    QwtPlotCurve(name)
{
    init();
}

PlotCurve::PlotCurve(QString name, QString style, const QVector<double>& x, const QVector<double> &y):
    QwtPlotCurve(name)
{
    init();
    setSamples(x, y);
    setStyle(style);
}

PlotCurve::~PlotCurve()
{
    plotCurves.removeOne(this);
}

void PlotCurve::init()
{
    setRenderHint(QwtPlotItem::RenderAntialiased);
    setLegendAttribute(QwtPlotCurve::LegendShowLine,  true);
    setLegendAttribute(QwtPlotCurve::LegendShowSymbol,true);
    plotCurves.push_back(this);
}

//The style set the pens for curve.
#include "../../Styles/StylesCurve.h"
void PlotCurve::setStyle(QString key)
{
    StyleCurve* style = StylesCurve::getInstance()->value(key);
    if(style){
        setPen(style->pen);
        setSymbol(new QwtSymbol(*style->symbol));
        setBeginMarkerPoint(style->begin);
        setMarkerStep(style->step);
        styleCurve = key;
    }
}

void PlotCurve::reloadStyle()
{
    setStyle(styleCurve);
}


void PlotCurve::updateStyles()
{
    foreach(PlotCurve* curve, plotCurves)
        curve->reloadStyle();
}
