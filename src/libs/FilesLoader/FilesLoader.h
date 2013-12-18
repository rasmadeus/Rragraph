#ifndef FILESLOADER_H
#define FILESLOADER_H

#include <QObject>

class FilesLoader : public QObject
{
    Q_OBJECT
public:
    explicit FilesLoader(QObject *parent = 0);
Q_SIGNALS:

};

#endif // FILESLOADER_H
