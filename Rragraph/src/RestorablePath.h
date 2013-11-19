#ifndef RESTORABLEPATH_H
#define RESTORABLEPATH_H

#include <QString>
class QFileInfo;

class RestorablePath
{
public:
    RestorablePath(const QString& key);
    ~RestorablePath();
    QString operator () ();
    void operator = (const QString& path);
    QFileInfo getInfoPath() const;
    const QString& getPath() const;
    void clearPath();
private:
    QString path;
    const QString key;
};

#endif // RESTORABLEPATH_H
