#ifndef CURVESTYLEMODEL_H
#define CURVESTYLEMODEL_H

#include "../Model.h"

class CurveStyleModel : public Model
{
    Q_OBJECT
public:
    explicit CurveStyleModel(QObject* parent = 0);
private:
    void insertNewStyle(int row);
};

#endif // CURVESTYLEMODEL_H
