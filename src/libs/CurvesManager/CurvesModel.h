#ifndef CURVESMODEL_H
#define CURVESMODEL_H

class Plot;
class Curve;
class Curves;
#include "ListModel.h"

class CurvesModel : public ListModel
{
    Q_OBJECT
public:
    explicit CurvesModel(QObject *parent = 0);
    void setCurves(Curves* curves);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    Curve* getCurve() const;
    Plot* getOwner() const;
    Curves* getCurves() const;
protected:
    QString displayRole(const QModelIndex& index) const;
private:
    Curves* curves;
};

#endif // CURVESMODEL_H
