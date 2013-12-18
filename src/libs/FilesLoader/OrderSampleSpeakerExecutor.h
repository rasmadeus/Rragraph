#ifndef ORDERSAMPLESPEAKEREXECUTOR_H
#define ORDERSAMPLESPEAKEREXECUTOR_H

class SampleSpeaker;
#include <QList>

class OrderSampleSpeakerExecutor
{
public:
    OrderSampleSpeakerExecutor(SampleSpeaker* speaker);
    virtual ~OrderSampleSpeakerExecutor();
    virtual void samplesIsAboutToReload(int i) = 0;
    virtual void samplesIsAboutToRemove(int i) = 0;
    virtual void samplesHaveBeenAppend(int i) = 0;
    virtual void samplesHaveBeenLoaded(int i) = 0;
    virtual void samplesHaveBeenRemoved(int i) = 0;
protected:
    SampleSpeaker* speaker;
};

#endif // ORDERSAMPLESPEAKERECUTOR_H
