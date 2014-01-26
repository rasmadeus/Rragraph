#ifndef GROUPPROCREATOR_H
#define GROUPPROCREATOR_H

class CurvesProCreator;
class PlotProCreator;
#include "ObjectProCreator.h"
#include <QJsonArray>

class GroupProCreator: public ObjectProCreator
{
public:
    void clear();
    void fill(QJsonArray& groups) const;
    void appendFile(const QString& relativePath);
    void appendPlot(const PlotProCreator& plot);
    void appendCurve(const CurvesProCreator& curves);
    void setTitle(const QString& title);
protected:
    QJsonArray files;
    QJsonArray plots;
    QJsonArray curves;
};

#endif // GROUPPROCREATOR_H
