#ifndef LOADER_H
#define LOADER_H

class Samples;
#include <QThread>

class Loader : public QThread
{
    Q_OBJECT
public:
    explicit Loader(Samples* samples, QObject *parent = 0);
    ~Loader();
signals:
    void wasLoaded(Samples* samples);
    void headersWasParsed(Samples* samples);
private:
    void run();
    void fillHeaders(const QString& firstRow);
    void append(const QString& row);
    void rearrange(QStringList& column);
    Samples* samples;
};

#endif // LOADER_H
