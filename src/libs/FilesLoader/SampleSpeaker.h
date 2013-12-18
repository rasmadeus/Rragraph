#ifndef SAMPLESPEAKER_H
#define SAMPLESPEAKER_H

#include "OrderSampleSpeakerExecutor.h"
#include "SamplesManager.h"

class SampleSpeaker : public SamplesManager
{
    Q_OBJECT
public:
    explicit SampleSpeaker(QObject *parent = 0);
    void addExecutor(OrderSampleSpeakerExecutor* executor);
    void removeExecutor(OrderSampleSpeakerExecutor* executor);
private slots:
    void samplesIsAboutToReload(int i);
    void samplesIsAboutToRemove(int i);
    void samplesHaveBeenAppend(int i);
    void samplesHaveBeenLoaded(int i);
    void samplesHaveBeenRemoved(int i);
private:
    QList<OrderSampleSpeakerExecutor*> executors;
};

#endif // SAMPLESPEAKER_H
