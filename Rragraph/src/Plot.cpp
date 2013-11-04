#include "Plot.h"

#include <qwt_plot_canvas.h>
#include "Canvas.h"
#include "Grid.h"
#include "Files.h"
#include "LegendItem.h"
Plot::Plot(QWidget *parent) :
    QwtPlot(parent),
    controlIsPressed(false),
    exportSize(100, 100)
{
    grid = new Grid(this);
    legend = new LegendItem(this);
    setPalette(QPalette(Qt::white));
    canvas = new Canvas(this);

    for(int i = 0; i< Files::getInstance()->countSamples(); ++i){
        wasAdded(i);
    }

    setAxisAutoScale(xBottom, false);
    setAxisAutoScale(yLeft, false);

    connect(canvas, SIGNAL(zoomed()), SIGNAL(zoomed()));
    connect(Files::getInstance(), SIGNAL(wasAdded(int)), SLOT(wasAdded(int)));
    connect(Files::getInstance(), SIGNAL(wasRemoved(int)), SLOT(wasRemoved(int)));
}

#include "Curves.h"
Plot::~Plot(){
    delete legend;
    qDeleteAll(samples);
}

Curves* Plot::getCurves(int iFile){
    return samples.value(iFile, nullptr);
}

LegendItem* Plot::getLegend(){
    return legend;
}

void Plot::wasRemoved(int iFile){
    delete samples.take(iFile);
}

void Plot::wasAdded(int iFile)
{
    wasRemoved(iFile);
    samples[iFile] = new Curves(iFile, this);
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

#include "CurveSettingsView.h"
void Plot::mousePressEvent(QMouseEvent* evt)
{
    if(!controlIsPressed && evt->button() == Qt::RightButton){
        CurveSettingsView::getInstance()->setOwner(this);
        CurveSettingsView::getInstance()->show();
    }
}

void Plot::autoSize()
{
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

void Plot::setExportSize(const QSizeF& size){
    exportSize = size;
}

const QSizeF& Plot::getExportSize() const{
    return exportSize;
}

double Plot::axiStep(Axis axis) const
{
    const QList<double> ticks = axisScaleDiv(axis).ticks(QwtScaleDiv::MajorTick);
    return ticks.size() > 1 ? ticks[1] - ticks[0] : 0;
}

static QJsonObject serializeAxis(const Plot* plot, Plot::Axis axis)
{
    QJsonObject obj;
    const QwtInterval interval = plot->axisInterval(axis);
    obj["min"] = interval.minValue();
    obj["max"] = interval.maxValue();
    obj["step"] = plot->axiStep(axis);
    const QString title = plot->axisTitle(axis).text();
    if(!title.isEmpty()){
        obj["title"] = plot->axisTitle(axis).text();
    }
    return obj;
}

static void parseAxis(Plot* plot, Plot::Axis axis, const QJsonObject& obj)
{
    plot->setAxisScale(
        axis,
        obj.value("min").toVariant().toDouble(),
        obj.value("max").toVariant().toDouble(),
        obj.value("step").toVariant().toDouble()
    );
    plot->setAxisTitle(axis, obj.value("title").toVariant().toString());
}

static QJsonObject serializeSizeF(const QSizeF& size)
{
    QJsonObject obj;
    obj["width"] = size.width();
    obj["height"] = size.height();
    return obj;
}

static void parseSizeF(Plot* plot, const QJsonObject& obj)
{
    plot->setExportSize(
        QSizeF(
            obj.value("width").toVariant().toDouble(),
            obj.value("height").toVariant().toDouble()
        )
    );
}

QJsonObject Plot::serialize() const
{
    QJsonObject obj;
    obj["exportSize"] = serializeSizeF(exportSize);
    obj["absciss"] = serializeAxis(this, xBottom);
    obj["ordinate"] = serializeAxis(this, yLeft);
    return obj;
}

void Plot::restore(const QJsonObject& obj)
{
    parseSizeF(this, obj.value("exportSize").toObject());
    parseAxis(this, xBottom, obj.value("absciss").toObject());
    parseAxis(this, yLeft, obj.value("ordinate").toObject());
}
