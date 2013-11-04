#ifndef SAVABLE_H
#define SAVABLE_H

#include <QJsonObject>

class Savable
{
public:
    virtual ~Savable();
    virtual void restore(const QJsonObject& obj) = 0;
    virtual QJsonObject serialize() const = 0;
};

#endif // SAVABLE_H
