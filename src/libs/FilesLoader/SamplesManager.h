#ifndef SAMPLESMODEL_H
#define SAMPLESMODEL_H

class Path;
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
    bool samplesExist(int i) const;
    int count() const;
    Samples* append(const QString& pathToSrc);
    void append(const QStringList& paths);
    void remove(int i);
    void reload(int i);
    void replace(int i, const QString& pathToSrc);
    Samples* getSamples(int i) const;
    const QVector<Samples*>& getSamples() const;
    void serialize(QJsonObject& groupSettings, const Path& proPath) const;
    void restore(const QJsonObject& groupSettings, const Path& proPath);
public Q_SLOTS:
    void clear();
Q_SIGNALS:
    void isAboutToReload(int i);
    void isAboutToRemove(int i);
    void haveBeenAdded(int i);
    void haveBeenLoaded(int i);
    void haveBeenRemoved(int i);
    void proxyDataWasChanged();
private slots:
    void haveBeenLoaded(Samples* samples);
private:
    QVector<Samples*> data;
};

#endif // SAMPLESMODEL_H
