#include "CurvesManager.h"

#include <SamplesManager.h>
CurvesManager::CurvesManager(SamplesManager* samplesManager, Plot* owner, QObject *parent):
    QObject(parent),
    samplesManager(samplesManager),
    owner(owner)
{
    {
        foreach (Samples* samples, samplesManager->getSamples()){
            pushBack(samples);
        }
    }
    {
        connect(samplesManager, SIGNAL(haveBeenAdded(int)), SLOT(newSamplesWasAdded(int)));
        connect(samplesManager, SIGNAL(haveBeenLoaded(int)), SLOT(samplesWasLoaded(int)));
        connect(samplesManager, SIGNAL(haveBeenRemoved(int)), SLOT(samplesIsGoingToRemove(int)));
        connect(samplesManager, SIGNAL(proxyDataWasChanged()), SLOT(resamples()));
        connect(samplesManager, SIGNAL(haveBeenLoaded(int)), SLOT(tryRestoreCurves(int)));
    }

}

CurvesManager::~CurvesManager()
{
    qDeleteAll(data);
}

SamplesManager* CurvesManager::getSamplesManager() const
{
    return samplesManager;
}

Plot* CurvesManager::getPlot() const
{
    return owner;
}

int CurvesManager::count() const
{
    return data.count();
}

Curves* CurvesManager::getCurves(int i) const
{
    return data[i];
}

void CurvesManager::newSamplesWasAdded(int i)
{
    pushBack(samplesManager->getSamples(i));
}

#include "Curves.h"
void CurvesManager::samplesWasLoaded(int i)
{
    data[i]->resamples();
}

void CurvesManager::samplesIsGoingToRemove(int i)
{
    delete data[i];
    data.remove(i);
}

void CurvesManager::pushBack(const Samples *samples)
{
    data << new Curves(owner, samples);
}

void CurvesManager::resamples()
{
    foreach(Curves* curves, data){
       curves->resamples();
    }
}

#include <QJsonObject>
#include <QJsonArray>
void CurvesManager::serialize(QJsonObject& plotSettings) const
{
    if(!data.isEmpty()){
        QJsonArray curvesSettings;
        foreach (Curves* curves, data){
            curves->serialize(curvesSettings);
        }
        plotSettings.insert("Curves", curvesSettings);
    }
}

void CurvesManager::restore(const QJsonObject& plotSettings)
{
    if(plotSettings.contains("Curves")){
        curvesSettings = plotSettings.value("Curves").toArray();
    }
}

void CurvesManager::tryRestoreCurves(int i)
{
    if(data[i]->isEmpty() && curvesSettings.size() > i){
        data[i]->restore(curvesSettings[i].toObject());
    }
}
