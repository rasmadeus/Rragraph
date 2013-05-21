#include "StylesCurve.h"

StylesCurve::StylesCurve()
{
    fill();
}

StylesCurve::~StylesCurve()
{
    release();
}

StylesCurve* StylesCurve::instance = 0;

StylesCurve* StylesCurve::getInstance()
{
    if(!instance) instance = new StylesCurve();
    return instance;
}

StyleCurve* StylesCurve::value(const QString& key)
{
    return data.value(key, 0);
}

void StylesCurve::update()
{
    release();
    fill();
}

#include <QComboBox>
void StylesCurve::fill(QComboBox* cb)
{
    cb->addItems(data.keys());
}

#include <QSettings>
#include "Item/Item.h"
#include "StyleReader.h"
void StylesCurve::fill()
{
    QSettings settings;
    settings.beginGroup("Styles/" + Item::getCaption(Item::ROOT_CURVE));
    foreach(QString key, settings.childGroups()){
        StyleCurve* style = new StyleCurve();
        StyleReader::fill(key, style);
        data[key] = style;
    }
}

void StylesCurve::release()
{
    qDeleteAll(data);
    data.clear();
}
