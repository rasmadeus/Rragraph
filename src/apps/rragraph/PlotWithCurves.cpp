#include "PlotWithCurves.h"

#include <CurvesManager.h>
PlotWithCurves::PlotWithCurves(SamplesManager* samplesManager, CurvesManagerView* curvesManagerView, QWidget* parent) :
    Plot(parent),
    curvesManagerView(curvesManagerView)
{
    curvesManager = new CurvesManager(samplesManager, this);
    setPalette(QPalette(Qt::white));
}

PlotWithCurves::~PlotWithCurves()
{
    delete curvesManager;
}

#include <CurvesManagerView.h>
#include <CurvesManagerView.h>
#include <QMouseEvent>
void PlotWithCurves::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::RightButton){
        if(controlIsPressed){
            setZoomBase();
            replot();
        }
        else{
            curvesManagerView->setCurvesManager(curvesManager);
            curvesManagerView->show();
        }
    }
    Plot::mousePressEvent(event);
}

#include <QJsonArray>
#include <QJsonObject>
void serializeQwtText(const QwtText& qwtText, const QString& prefix, QJsonObject& obj)
{
    if(!qwtText.isEmpty()){
        obj.insert(prefix, qwtText.text());
        obj.insert(prefix + "Color", QJsonValue::fromVariant(qwtText.color()));
        obj.insert(prefix + "Font", QJsonValue::fromVariant(qwtText.font()));
    }
}

QwtText restoreQwtText(const QString& prefix, const QJsonObject& obj)
{
    QwtText qwtText;
    if(obj.contains(prefix)){
        qwtText.setText(obj.value(prefix).toString());
        qwtText.setColor(obj.value(prefix + "Color").toVariant().value<QColor>());
        qwtText.setFont(obj.value(prefix + "Font").toVariant().value<QFont>());
    }
    return qwtText;
}

void serializeSizeF(const QSizeF& sizeF, const QString& key, QJsonObject& obj)
{
    obj.insert(
       key,
       QString("%1 %2")
           .arg(sizeF.width())
           .arg(sizeF.height())
    );
}

QSizeF restoreSizeF(const QString& key, const QJsonObject& obj)
{
    QStringList part = obj.value(key).toString().split(" ");
    while(part.size() < 2){
        part << "100";
    }
    return QSizeF(part.first().toDouble(), part.last().toDouble());
}

#include <LegendItem.h>
void PlotWithCurves::serialize(QJsonArray& plots) const
{
    QJsonObject plotSettings;
        serializeAxis(xBottom, "x", plotSettings);
        serializeAxis(yLeft, "y", plotSettings);
        serializeQwtText(title(), "title", plotSettings);
        serializeSizeF(getExportSize(), "exportSize", plotSettings);
        plotSettings.insert("resolution", getResolution());
        legend->serialize(plotSettings);
        curvesManager->serialize(plotSettings);
    plots.append(plotSettings);
}

#include <qwt_point_3d.h>
void PlotWithCurves::restore(const QJsonObject& plotSettings)
{
    xBase = restoreAxis(xBottom, "x", plotSettings);
    yBase = restoreAxis(yLeft, "y", plotSettings);
    setResolution(plotSettings.value("resolution").toInt(150));
    setTitle(restoreQwtText("title", plotSettings));
    setZoomStack();
    setExportSize(restoreSizeF("exportSize", plotSettings));
    legend->restore(plotSettings);
    curvesManager->restore(plotSettings);
    setZoomBase();
}

void PlotWithCurves::serializeAxis(Axis axis, const QString& prefix, QJsonObject& plotSettings) const
{
    {
        serializeQwtText(axisTitle(axis), prefix + "Title", plotSettings);
    }
    {
        QwtInterval axisInterval = this->axisInterval(axis);
        plotSettings.insert(prefix + "Min", axisInterval.minValue());
        plotSettings.insert(prefix + "Max", axisInterval.maxValue());
        plotSettings.insert(prefix + "Step", axisStep(axis));
    }
}


QwtPoint3D PlotWithCurves::restoreAxis(Axis axis, const QString& prefix, const QJsonObject& plotSettings)
{
        setAxisTitle(axis, restoreQwtText(prefix + "Title", plotSettings));
        return QwtPoint3D(
            plotSettings.value(prefix + "Min").toDouble(0),
            plotSettings.value(prefix + "Max").toDouble(100),
            plotSettings.value(prefix + "Step").toDouble(10)

        );
}
