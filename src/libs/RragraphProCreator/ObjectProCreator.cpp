#include "ObjectProCreator.h"

#include <QJsonObject>
void ObjectProCreator::clear()
{
    obj = QJsonObject();
}

void ObjectProCreator::insertProperty(const QString& key, const QVariant& value)
{
    obj.insert(key, QJsonValue::fromVariant(value));
}

#include <QJsonArray>
void ObjectProCreator::fill(QJsonArray& objArray) const
{
    objArray.append(obj);
}
