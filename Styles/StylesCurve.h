#ifndef STYLESCURVE_H
#define STYLESCURVE_H

class QComboBox;
#include <QMap>

#include <QPen>
#include "../qwt-6.0.1/qwt_symbol.h"

struct StyleCurve
{
    QwtSymbol* symbol;
    QPen pen;

    StyleCurve()
    {
        symbol = 0;
        begin = 0;
        step = 10;
    }    

    ~StyleCurve()
    {
        if(symbol) delete symbol;
    }

    int begin;
    int step;
};


class StylesCurve
{
private:
    StylesCurve(const StylesCurve&);
    StylesCurve& operator  = (const StylesCurve&);
protected:
    StylesCurve();
public:
    static StylesCurve* getInstance();
    ~StylesCurve();
    StyleCurve* value(const QString& key);
    void update();
    void fill(QComboBox* cb);
private:
    void release();
    void fill();
private:
    QMap<QString, StyleCurve*> data;
    static StylesCurve* instance;
};

#endif // STYLESCURVE_H
