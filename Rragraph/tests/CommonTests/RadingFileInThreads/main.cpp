#include <QCoreApplication>

#include "../../../src/Samples.h"
#include "../../../src/Loader.h"
#include "Consumer.h"
#include <QDebug>
#include <QFileInfo>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Start**********************************************************";
    QFileInfo fi("../../../../../Rragraph/Rragraph/tests/testData/bigFile.txt");
    qDebug() << fi.exists();
    Samples* samples = new Samples(fi.absoluteFilePath());
    Loader* loader = new Loader(samples);
    loader->start();
    Consumer* consumer = new Consumer(samples);
    consumer->start();
    while(loader->isRunning());
    delete consumer;
    delete loader;
    delete samples;
    qDebug() << "end************************************************************";
    return a.exec();
}
