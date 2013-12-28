#ifndef FILES_H
#define FILES_H

#include "Samples.h"
#include "Loader.h"
#include "global.h"
#include <QObject>
#include "RestorablePath.h"

class Files : public QObject
{
    Q_OBJECT
    SINGLETON_HEADER(Files, QObject)
public:
    ~Files();
    void load(const QStringList& paths);
    void remove(int iFile);
    void removeAll();
    void reload(int iFile, const QString& path);
    void reload(int iFile);
    const QVector<qreal>& getSamples(int iFile, int i) const;
    const QStringList& getHeaders(int iFile) const;
    int countSamples(int iFile) const;
    int countSamples() const;
    bool isOutOfRange(int iFile) const;
    bool isOutOfRange(int iFile, int i) const;
    QFileInfo getPath(int iFile) const;
    QString getRelativePath(int iFile) const;
    QString getLastLoadedFilePath();
    bool isLoading(int iFile) const;
    bool allWasLoaded() const;
    void serialize(QJsonObject& root);
    void restore(QJsonObject& root);
public slots:
    void load();
signals:
    void wasRemovedAll();
    void headersWasParsed(int iFile);
    void wasLoaded(int iFile);
    void wasRemoved(int iFile);
    void wasAdded(int iFile);
private slots:
    void wasLoaded(Samples* samples);
    void headersWasParsed(Samples* samples);
private:
    RestorablePath lastLoadedFilePath;
    QVector<Loader*> loaders;
    QVector<Samples*> samples;
};

#endif // FILES_H
