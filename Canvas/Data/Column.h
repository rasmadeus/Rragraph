#ifndef COLUMN_H
#define COLUMN_H

#include <QVector>
#include <QString>

class Column
{
public:
    explicit Column(QString getHeader = QString());
    void pushBackValue(float value);
    QString getHeader() const;
    const QVector<double>& getValues() const;
    QVector<double> getValues(float mult) const;
    void clearValues();
private:
    QString header;
    QVector<double> values;
};

#endif // COLUMN_H
