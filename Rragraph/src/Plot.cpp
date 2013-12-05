#include "Plot.h"

#include <qwt_plot_canvas.h>
#include "Canvas.h"
#include "Grid.h"
#include "Files.h"
#include "LegendItem.h"
#include "HeaderSamples.h"
Plot::Plot(QWidget *parent) :
    QwtPlot(parent),
    controlIsPressed(false),
    exportSize(100, 100),
    curvesIsRestoring(false)
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
    connect(Files::getInstance(),     SIGNAL(wasAdded(int)),   SLOT(wasAdded(int)));
    connect(Files::getInstance(),     SIGNAL(wasRemoved(int)), SLOT(wasRemoved(int)));

    connect(
        HeaderSamples::getInstance(),
        SIGNAL(headerWasChanged(int,int,QString)),
        SLOT(headerWasChanged(int,int,QString))
    );

}
#include <QDebug>
#include "Curves.h"
Plot::~Plot(){
    delete legend;
    qDeleteAll(curves);
}

Curves* Plot::getCurves(int iFile){
    if(iFile < 0 || iFile >= curves.size()){
        return nullptr;
    }
    return curves[iFile];
}

LegendItem* Plot::getLegend(){
    return legend;
}

void Plot::wasRemoved(int iFile){
    for(int i = iFile + 1; i < this->curves.size(); ++i){
        this->curves[i]->wasRemoved();
    }
    Curves* curves = this->curves[iFile];
    this->curves.remove(iFile);
    delete curves;
    replot();
}

void Plot::wasAdded(int iFile)
{
    if(iFile < curves.size()){
        delete this->curves[iFile];
        curves[iFile] = new Curves(iFile, this);
    }
    else{
        curves.push_back(new Curves(iFile, this));
    }
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

void Plot::headerWasChanged(int iFile, int i, const QString& header){
    curves[iFile]->headerWasChanged(iFile, i, header);
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

void Plot::setExportSize(const QSizeF& size){
    exportSize = size;
}

const QSizeF& Plot::getExportSize() const{
    return exportSize;
}

double Plot::axiStep(Axis axis) const
{
    const QList<double> ticks = axisScaleDiv(axis).ticks(QwtScaleDiv::MajorTick);
    return (ticks.size() > 1) ? (ticks[1] - ticks[0]) : 0;
}

#include <QJsonObject>
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

static QJsonObject serializeTitle(const QwtText& text)
{
    QJsonObject obj;
    obj["text"] = text.text();
    obj["color"] = QJsonValue::fromVariant(text.color());
    obj["font"] =  QJsonValue::fromVariant(text.font());
    return obj;
}

static void parseTitle(Plot* plot, const QJsonObject& obj)
{
    QwtText text;
    text.setText(obj.value("text").toString());
    text.setColor(obj.value("color").toVariant().value<QColor>());
    text.setFont(obj.value("font").toVariant().value<QFont>());
    plot->setTitle(text);
}



#include <QJsonArray>
void Plot::serialize(QJsonArray& plots) const
{
    QJsonObject plot;
    plot["axisX"] = serializeAxis(this, xBottom);
    plot["axisY"] = serializeAxis(this, yLeft);
    plot["exportSize"] = serializeSizeF(exportSize);
    if(!title().text().isEmpty()){
        plot["title"] = serializeTitle(title());
    }
    legend->serialize(plot);
    plots.push_back(plot);
}

void Plot::restore(const QJsonValue& value)
{
    const QJsonObject plot = value.toObject();
    parseAxis(this, xBottom, plot.value("axisX").toObject());
    parseAxis(this, yLeft, plot.value("axisY").toObject());
    parseSizeF(this, plot.value("exportSize").toObject());
    if(plot.contains("title")){
        parseTitle(this, plot.value("title").toObject());
    }
    legend->restore(plot);
    replot();
}

void Plot::serializeCurves(QJsonArray& plots) const
{
    QJsonArray curves;
    foreach(Curves* item, this->curves){
        QJsonObject plot;
        item->serialize(plot);
        curves.push_back(plot);
    }
    plots.push_back(curves);
}

void Plot::restoreCurves(int iFile, const QJsonObject& plot)
{
    if(iFile < 0 || iFile >= this->curves.size()){
        return;
    }
    curvesIsRestoring = true;
        this->curves[iFile]->restore(plot);
    curvesIsRestoring = false;
}

bool Plot::isCurvesRestoring() const{
    return curvesIsRestoring;
}
