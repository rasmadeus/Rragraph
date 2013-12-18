#include "OrderSampleSpeakerExecutor.h"

#include "SampleSpeaker.h"
OrderSampleSpeakerExecutor::OrderSampleSpeakerExecutor(SampleSpeaker* speaker):
    speaker(speaker)
{
    speaker->addExecutor(this);
}

OrderSampleSpeakerExecutor::~OrderSampleSpeakerExecutor()
{
    speaker->removeExecutor(this);
}
