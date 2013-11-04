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
    SINGLETON_HEADER(Files)
    RestorablePath lastLoadedFilePath;
    QVector<Loader*> loaders;
    QVector<Samples*> samples;
public:
    ~Files();
    void load(const QStringList& paths);
    void remove(int iFile);
    void reload(int iFile, const QString& path);
    void reload(int iFile);
    const QVector<qreal>& getSamples(int iFile, int i) const;
    const QStringList& getHeaders(int iFile) const;
    int countSamples(int iFile) const;
    int countSamples() const;
    QFileInfo getPath(int iFile) const;
    QString getLastLoadedFilePath();
    bool isLoading(int iFile) const;
public slots:
    void load();
signals:
    void headersWasParsed(int iFile);
    void wasLoaded(int iFile);
    void wasRemoved(int iFile);
    void wasAdded(int iFile);
private slots:
    void wasLoaded(Samples* samples);
    void headersWasParsed(Samples* samples);
};

#endif // FILES_H
