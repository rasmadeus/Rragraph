#include "SamplesManager.h"

SamplesManager::SamplesManager(QObject *parent) :
    QObject(parent)
{
}

SamplesManager::~SamplesManager()
{
    qDeleteAll(data);
}

int SamplesManager::count() const
{
    return data.count();
}

#include "Samples.h"
void SamplesManager::append(const QString& pathToSrc)
{
    Samples* samples = new Samples();
    data.push_back(samples);
    emit haveBeenAdded(count() - 1);
    connect(samples, SIGNAL(haveBeenLoaded(Samples*)), SLOT(haveBeenLoaded(Samples*)));
    connect(samples, SIGNAL(proxyDataWasChanged()), SIGNAL(proxyDataWasChanged()));
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

void SamplesManager::replace(int i, const QString& pathToSrc)
{
    data[i]->load(pathToSrc);
}


void SamplesManager::clear()
{
    while(count()){
        remove(0);
    }
}

Samples* SamplesManager::getSamples(int i) const
{
    return data[i];
}

const QVector<Samples*>& SamplesManager::getSamples() const
{
    return data;
}

bool SamplesManager::samplesExist(int i) const
{
    return i >= 0 && i < count();
}
