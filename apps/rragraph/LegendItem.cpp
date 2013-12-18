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

#include <QJsonArray>
#include <QFlags>
#include <QJsonObject>
void LegendItem::serialize(QJsonObject& plot)
{
    QJsonObject legend;
    legend["horizontalPos"] =  int(getHorPos());
    legend["verticalPos"] = int(getVerPos());
    legend["isVisible"] = QJsonValue::fromVariant(isVisible());
    legend["maxColumns"]  = QJsonValue::fromVariant(maxColumns());
    legend["font"] = QJsonValue::fromVariant(font());
    legend["backgroundAlpha"] = QJsonValue::fromVariant(borderPen().color().alpha());
    plot["legend"] = legend;
}

void LegendItem::restore(const QJsonObject& plot)
{
    const QJsonObject legend = plot.value("legend").toObject();
    setAlignment(
        Qt::AlignmentFlag(legend.value("horizontalPos").toVariant().toInt()) |
        Qt::AlignmentFlag(legend.value("verticalPos").toVariant().toInt())

    );
    setMaxColumns(legend.value("maxColumns").toVariant().toUInt());
    setFont(legend.value("font").toVariant().value<QFont>());
    setBackgroundOpacity(legend.value("backgroundAlpha").toVariant().toInt());
    setVisible(legend.value("isVisible").toBool(true));
}
