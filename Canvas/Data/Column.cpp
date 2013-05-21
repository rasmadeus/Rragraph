#include "Column.h"
#include <QObject>

Column::Column(QString header):
    header(header)
{
}

void Column::pushBackValue(float value)
{
    values.push_back(value);
}

QString Column::getHeader() const
{
    return header;
}

const QVector<double> &Column::getValues() const
{
    return values;
}

QVector<double> Column::getValues(float mult) const
{
    QVector<double> result;
    foreach(double value, values) result << value * mult;
    return result;
}

void Column::clearValues()
{
    values.clear();
}
