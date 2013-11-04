#ifndef RESTORABLEPATH_H
#define RESTORABLEPATH_H

#include <QString>
class RestorablePath
{
    QString path;
    const QString key;
public:
    RestorablePath(const QString& key);
    ~RestorablePath();
    QString operator () ();
    void operator = (const QString& path);
};

#endif // RESTORABLEPATH_H
