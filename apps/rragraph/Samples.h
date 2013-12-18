#ifndef SAMPLES_H
#define SAMPLES_H

class QFileInfo;
#include <QStringList>
#include <QVector>

class Samples
{
public:
    Samples(const QString& path);
    void pushBack(const QString& header);
    void pushBack(int i, qreal sample);
    const QStringList& getHeaders() const;
    const QVector<QVector<qreal> > getSamples() const;
    void setPath(const QString& path);
    QFileInfo getPath() const;
    void clear();
private:
    QStringList headers;
    QVector<QVector<qreal> > samples;
    QString path;
};

#endif // SAMPLES_H
