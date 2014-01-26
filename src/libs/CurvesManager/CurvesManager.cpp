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
    delete data.takeAt(i);
}

void CurvesManager::pushBack(const Samples *samples)
{
    data << new Curves(owner, samples);
}
