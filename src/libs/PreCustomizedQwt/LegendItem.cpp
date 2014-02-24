#include "LegendItem.h"

#include <qwt_plot.h>
LegendItem::LegendItem(QwtPlot* owner)
{
    setRenderHint(QwtPlotItem::RenderAntialiased);
    setTextPen(QPen(Qt::black));
    setBackgroundOpacity(200);
    setBackgroundMode(ItemBackground);
    setBorderRadius(4);
    setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    setMargin(0);
    setSpacing(4);
    setItemMargin(2);    
    attach(owner);
}

void LegendItem::setBackgroundOpacity(int alpha)
{
    setBorderPen(QPen(QColor(0, 0, 0, alpha)));
    setBackgroundBrush(QColor(255, 255, 255, alpha));
}

Qt::AlignmentFlag LegendItem::getHorPos() const
{
    if(alignment().testFlag(Qt::AlignHCenter)){
        return Qt::AlignHCenter;
    }
    if(alignment().testFlag(Qt::AlignLeft)){
        return Qt::AlignLeft;
    }
    return Qt::AlignRight;
}

Qt::AlignmentFlag LegendItem::getVerPos() const
{
    if(alignment().testFlag(Qt::AlignVCenter)){
        return Qt::AlignVCenter;
    }
    if(alignment().testFlag(Qt::AlignTop)){
        return Qt::AlignTop;
    }
    return Qt::AlignBottom;
}

#include <QJsonObject>
void LegendItem::serialize(QJsonObject& plotSettings) const
{
    plotSettings.insert("legendVisibility", QJsonValue::fromVariant(isVisible()));
    plotSettings.insert("legendHorPos", QJsonValue::fromVariant(getHorPos()));
    plotSettings.insert("legendVerPos", QJsonValue::fromVariant(getVerPos()));
    plotSettings.insert("legendBackgroundOpacity", QJsonValue::fromVariant(backgroundBrush().color().alpha()));
    plotSettings.insert("legendFont", QJsonValue::fromVariant(font()));
    plotSettings.insert("legendColumns", QJsonValue::fromVariant(maxColumns()));
}

void LegendItem::restore(const QJsonObject& plotSettings)
{
    setVisible(plotSettings.value("legendVisibility").toBool());
    setAlignment(
        Qt::AlignmentFlag(plotSettings.value("legendHorPos").toVariant().toInt()) |
        Qt::AlignmentFlag(plotSettings.value("legendVerPos").toVariant().toInt())
    );
    setBackgroundOpacity(plotSettings.value("legendBackgroundOpacity").toVariant().toInt());
    setFont(plotSettings.value("legendFont").toVariant().value<QFont>());
    setMaxColumns(plotSettings.value("legendColumns").toVariant().value<uint>());
}
