#include "SampleSpeaker.h"

SampleSpeaker::SampleSpeaker(QObject *parent) :
    SamplesManager(parent)
{
    connect(this, SIGNAL(isAboutToReload(int)), SLOT(samplesIsAboutToReload(int)));
    connect(this, SIGNAL(isAboutToRemove(int)), SLOT(samplesIsAboutToRemove(int)));
    connect(this, SIGNAL(haveBeenAppend(int)), SLOT(samplesHaveBeenAppend(int)));
    connect(this, SIGNAL(haveBeenLoaded(int)), SLOT(samplesHaveBeenLoaded(int)));
    connect(this, SIGNAL(haveBeenRemoved(int)), SLOT(samplesHaveBeenRemoved(int)));
}

void SampleSpeaker::addExecutor(OrderSampleSpeakerExecutor* executor)
{
    executors.append(executor);
}

void SampleSpeaker::removeExecutor(OrderSampleSpeakerExecutor* executor)
{
    executors.removeOne(executor);
}

void SampleSpeaker::samplesIsAboutToReload(int i)
{
    foreach(OrderSampleSpeakerExecutor* executor, executors){
        executor->samplesIsAboutToReload(i);
    }
}

void SampleSpeaker::samplesIsAboutToRemove(int i)
{
    foreach(OrderSampleSpeakerExecutor* executor, executors){
        executor->samplesIsAboutToRemove(i);
    }
}

void SampleSpeaker::samplesHaveBeenAppend(int i)
{
    foreach(OrderSampleSpeakerExecutor* executor, executors){
        executor->samplesHaveBeenAppend(i);
    }
}

void SampleSpeaker::samplesHaveBeenLoaded(int i)
{
    foreach(OrderSampleSpeakerExecutor* executor, executors){
        executor->samplesHaveBeenLoaded(i);
    }
}

void SampleSpeaker::samplesHaveBeenRemoved(int i)
{
    foreach(OrderSampleSpeakerExecutor* executor, executors){
        executor->samplesHaveBeenRemoved(i);
    }
}
