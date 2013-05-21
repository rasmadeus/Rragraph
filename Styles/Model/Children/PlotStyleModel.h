#ifndef PLOTSTYLEMODEL_H
#define PLOTSTYLEMODEL_H

#include "../Model.h"

class PlotStyleModel : public Model
{
    Q_OBJECT
public:
    explicit PlotStyleModel(QObject *parent = 0);
private:
    void insertNewStyle(int row);
};

#endif // PLOTSTYLEMODEL_H
