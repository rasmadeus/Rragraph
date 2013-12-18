#include "Plot.h"

#include <qwt_plot_canvas.h>
#include "Canvas.h"
#include "Grid.h"
#include "LegendItem.h"
Plot::Plot(QWidget *parent) :
    QwtPlot(parent),
    controlIsPressed(false),
    exportSize(100, 100)
{
    grid = new Grid(this);
    legend = new LegendItem(this);
    canvas = new Canvas(this);

    setPalette(QPalette(Qt::white));

    setAxisAutoScale(xBottom, false);
    setAxisAutoScale(yLeft, false);

    connect(canvas, SIGNAL(zoomed()), SIGNAL(zoomed()));
}

Plot::~Plot()
{
    delete legend;
}

LegendItem* Plot::getLegend()
{
    return legend;
}

#include <QKeyEvent>
void Plot::keyPressEvent(QKeyEvent* evt)
{
    if(evt->key() == Qt::Key_Control){
        controlIsPressed = true;
    }
    QwtPlot::keyPressEvent(evt);
}

void Plot::keyReleaseEvent(QKeyEvent* evt)
{
    if(evt->key() == Qt::Key_Control){
        controlIsPressed = false;
    }
    QwtPlot::keyReleaseEvent(evt);
}

void Plot::autoSize()
{
    canvas->setZoomBase();
    setAxisAutoScale(xBottom);
    setAxisAutoScale(yLeft);
    replot();
    setAxisAutoScale(xBottom, false);
    setAxisAutoScale(yLeft, false);
}

void Plot::mouseDoubleClickEvent(QMouseEvent* evt)
{
    Q_UNUSED(evt)
    autoSize();
}

void Plot::setExportSize(const QSizeF& size)
{
    exportSize = size;
}

const QSizeF& Plot::getExportSize() const
{
    return exportSize;
}

double Plot::axiStep(Axis axis) const
{
    const QList<double> ticks = axisScaleDiv(axis).ticks(QwtScaleDiv::MajorTick);
    return (ticks.size() > 1) ? (ticks[1] - ticks[0]) : 0;
}
