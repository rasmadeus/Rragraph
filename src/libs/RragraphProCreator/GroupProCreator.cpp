#include "GroupProCreator.h"

void GroupProCreator::clear()
{
    curves = files = plots = QJsonArray();
    ObjectProCreator::clear();
}

void GroupProCreator::fill(QJsonArray& groups) const
{
    obj.insert("files", files);
    obj.insert("plots", plots);
    obj.insert("setCurves", curves);
    groups.append(obj);
}

#include <QVariant>
void GroupProCreator::appendFile(const QString& relativePath)
{
    files.append(QJsonValue::fromVariant(relativePath));
}

#include "PlotProCreator.h"
void GroupProCreator::appendPlot(const PlotProCreator& plot)
{
    plot.fill(plots);
}

#include "CurvesProCreator.h"
void GroupProCreator::appendCurve(const CurvesProCreator& curves)
{
    curves.fill(this->curves);
}

void GroupProCreator::setTitle(const QString& title)
{
    insertProperty("title", title);
}
