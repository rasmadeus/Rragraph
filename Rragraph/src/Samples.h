#ifndef SAMPLES_H
#define SAMPLES_H

#include <QStringList>
#include <QVector>
#include <QFileInfo>

class Samples
{
    QStringList headers;
    QVector<QVector<qreal> > samples;
    QString path;
public:
    Samples(const QString& path);
    void pushBack(const QString& header);
    void pushBack(int i, qreal sample);
    const QStringList& getHeaders() const;
    const QVector<QVector<qreal> > getSamples() const;
    void setPath(const QString& path);
    QFileInfo getPath() const;
    void clear();
};

#endif // SAMPLES_H
