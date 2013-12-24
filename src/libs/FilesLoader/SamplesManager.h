#ifndef SAMPLESMODEL_H
#define SAMPLESMODEL_H

class Samples;
#include <QObject>
#include <QMutex>
#include <QVector>

class SamplesManager : public QObject
{
    Q_OBJECT
public:
    explicit SamplesManager(QObject *parent = 0);
    ~SamplesManager();
    int count() const;
    int height(int i) const;
    void append(const QString& pathToSrc);
    void remove(int i);
    void reload(int i);
    int countSamples(int i) const;
    const QStringList& getHeaderSamples(int i) const;
    const QVector<double>& getColumnSamples(int i, int j) const;
    const QString& getPathToSamples(int i) const;
public Q_SLOTS:
    void clear();
Q_SIGNALS:
    void isAboutToReload(int i);
    void isAboutToRemove(int i);
    void haveBeenAppend(int i);
    void haveBeenLoaded(int i);
    void haveBeenRemoved(int i);
private slots:
    void haveBeenLoaded(Samples* samples);
private:
    QVector<Samples*> data;
};

#endif // SAMPLESMODEL_H
