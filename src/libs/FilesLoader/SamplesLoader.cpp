#include "SamplesLoader.h"

SamplesLoader::SamplesLoader(SamplesData* samplesData, QObject* parent):
    QThread(parent),
    samplesData(samplesData),
    stopCrane(true)
{
}

SamplesLoader::~SamplesLoader()
{
    stop
}

bool SamplesLoader::stop()
{
    stopCrane = true;
}
