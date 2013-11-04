#include "Consumer.h"

Consumer::Consumer(Samples* samples, QObject *parent) :
    QThread(parent),
    samples(samples)
{
}

Consumer::~Consumer()
{
    terminate();
    while(isRunning());
}

#include "../../../src/Samples.h"
#include <QDebug>
void Consumer::run()
{
    forever{
        qDebug() << samples->getHeaders();
        qDebug() << samples->getPath().absoluteFilePath();
        qDebug() << samples->getSamples();
    }
}
