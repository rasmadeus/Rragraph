#include "SamplesManager.h"

SamplesManager::SamplesManager(QObject *parent) :
    QObject(parent)
{
}

SamplesManager::~SamplesManager()
{
    qDeleteAll(data);
}

#include <QMutexLocker>
int SamplesManager::count() const
{
    return data.count();
}

#include "Samples.h"
void SamplesManager::append(const QString& pathToSrc)
{
    Samples* samples = new Samples();
    data.push_back(samples);
    emit haveBeenAppend(count());
    connect(samples, SIGNAL(haveBeenLoaded(Samples*)), SLOT(haveBeenLoaded(Samples*)));
    samples->load(pathToSrc);
}

void SamplesManager::haveBeenLoaded(Samples* samples)
{
    emit haveBeenLoaded(data.indexOf(samples));
}

void SamplesManager::remove(int i)
{
    emit isAboutToRemove(i);
    Samples* samples = data[i];
    data.remove(i);
    emit haveBeenRemoved(i);
    delete samples;
}

void SamplesManager::reload(int i)
{
    emit isAboutToReload(i);
    data[i]->reload();
}

int SamplesManager::countSamples(int i) const
{
    return data[i]->count();
}

const QStringList& SamplesManager::getHeaderSamples(int i) const
{
    return data[i]->getHeaders();
}

const QVector<double>& SamplesManager::getColumnSamples(int i, int j) const
{
    return data[i]->getColumns(j);
}

const QString& SamplesManager::getPathToSamples(int i) const
{
    return data[i]->getPathToSrc();
}
