#ifndef CURVESPROCREATOR_H
#define CURVESPROCREATOR_H

/*!
 * Класс предоставляет интерфейс для описания набора кривых.
 * Пример использования.
 * \code
 * ...
 * CurvesProCreator curves;
 * curves.setFile(0);
 * curves.setPlot(0);
 * curves.setX(0);
 * CurveProCreator curve;
 * curves.append(curve);
 * ...
 */



class CurveProCreator;
#include "ObjectProCreator.h"
#include <QJsonArray>

class CurvesProCreator: public ObjectProCreator
{
public:
    void clear();
    void fill(QJsonArray& parent) const;
    void append(const CurveProCreator& curve);
    void setX(int iX);
    void setFile(int iFile);
    void setPlot(int iPlot);
protected:
    QJsonArray curves;
};

#endif // CURVESPROCREATOR_H
