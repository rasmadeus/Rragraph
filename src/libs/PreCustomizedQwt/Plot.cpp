#include "Plot.h"
#include <qwt_plot_canvas.h>
#include "Canvas.h"
#include "Grid.h"
#include "LegendItem.h"

Path Plot::exportPath("paths/exportPath");

Plot::Plot(QWidget* parent) :
    QwtPlot(parent),
    controlIsPressed(false),
    exportSize(100, 100),
    resolution(150),
    xBase(0, 1000, 100),
    yBase(0, 1000, 100)
{
    setAutoFillBackground( true );
    grid = new Grid(this);
    legend = new LegendItem(this);
    canvas = new Canvas(this);
    setAxisAutoScale(xBottom, false);
    setAxisAutoScale(yLeft, false);
    connect(canvas, SIGNAL(zoomed()), SIGNAL(zoomed()));
}

void Plot::setZoomStack()
{
    const QRectF rect(QPointF(xBase.x(), yBase.x()), QPointF(xBase.y(), yBase.y()));
    setZoomBase();
    //canvas->setZoomStack(rect);
}

void Plot::setZoomBase()
{
    setAxisScale(xBottom, xBase.x(), xBase.y(), xBase.z());
    setAxisScale(yLeft, yBase.x(), yBase.y(), yBase.z());
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

void Plot::autoscale()
{
    canvas->setZoomBase();
    setAxisAutoScale(xBottom);
    setAxisAutoScale(yLeft);
    replot();
    setAxisAutoScale(xBottom, false);
    setAxisAutoScale(yLeft, false);
    emit zoomed();
}

void Plot::mouseDoubleClickEvent(QMouseEvent* evt)
{
    Q_UNUSED(evt)
    autoscale();    
}

void Plot::setExportSize(const QSizeF& size)
{
    exportSize = size;
}

const QSizeF& Plot::getExportSize() const
{
    return exportSize;
}

double Plot::axisStep(Axis axis) const
{
    const QList<double> ticks = axisScaleDiv(axis).ticks(QwtScaleDiv::MajorTick);
    return (ticks.size() > 1) ? (ticks[1] - ticks[0]) : 0;
}

#include <qwt_plot_renderer.h>
void Plot::exportToPng(QwtPlotRenderer& renderer, const QString& path)
{
    renderer.renderDocument(this, path, getExportSize(), resolution);
}

void Plot::exportToPng()
{
    const QString filter = tr("Images") + "(*.png);;" + Path::getTemplate(Path::ALL_FILES);
    if(Plot::exportPath.setSaveFileName(this, tr("Export current plot to image"), filter)){
        QwtPlotRenderer renderer;
        exportToPng(renderer, exportPath.getPath());
    }
}

void Plot::setResolution(int resolution)
{
    if(resolution >= 30){
        this->resolution = resolution;
    }
}

int Plot::getResolution() const
{
    return resolution;
}
