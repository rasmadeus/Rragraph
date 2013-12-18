#include "Canvas.h"
#include "Zoomer.h"
#include <qwt_plot.h>

Canvas::Canvas(QwtPlot* parent) :
    QwtPlotCanvas(parent)
{
    zoomer = new Zoomer(QwtPlot::xBottom, QwtPlot::yLeft, this);
    connect(zoomer, SIGNAL(zoomed(QRectF)), SIGNAL(zoomed()));
    setLineWidth(1);
    setFrameStyle(QFrame::Box | QFrame::Plain);
    setBorderRadius(10);
    parent->setCanvas(this);
    setPalette(QPalette(Qt::white));
}

void Canvas::setZoomBase(){
    zoomer->setZoomBase(false);
}
