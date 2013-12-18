#ifndef ROOT_H
#define ROOT_H

#include <QObject>

class Root : public QObject
{
    Q_OBJECT
public:
    explicit Root(QObject *parent = 0);

signals:

public slots:
private:
    QObject* data;
};

#endif // ROOT_H
