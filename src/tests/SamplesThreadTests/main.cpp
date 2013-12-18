#include <QCoreApplication>
#include <QThread>
#include "Samples.h"

class Base: public QThread
{
public:
    explicit Base(Samples* samples, QObject* parent = 0):
        QThread(parent),
        samples(samples)
    {
    }

    ~Base()
    {
        if(isRunning()){
            terminate();
            while(isRunning());
        }
    }

protected:
    Samples* samples;
};

#include <QDebug>
class Woodpecker: public Base
{
public:
    explicit Woodpecker(Samples* samples, QObject* parent = 0):
        Base(samples, parent)
    {
    }

protected:
    void run()
    {
        for(int i = 0; i < 10000; ++i)
        {
            qDebug() << "W";
                samples->count();
                samples->getHeaders();
                samples->getPathToSrc();
            qDebug() << "S";
        }
    }
};

#include <QFile>
#include <QTextStream>
class Loader: public Base
{
public:
    explicit Loader(Samples* samples, QObject* parent = 0):
        Base(samples, parent)
    {
        QFile testFile("SamplesThreadTest.txt");
        if(testFile.open(QFile::WriteOnly)){
            QTextStream out(&testFile);
            const int n = 100;
            for(int i = 0; i < 100; ++i){
                for(int j = 0; j < n; ++j){
                    out << i << " ";
                }
                out << "\n";
            }
        }
        samples->load("SamplesThreadTest.txt");
    }

    ~Loader()
    {
        QFile testFile("SamplesThreadTest.txt");
        testFile.remove();
    }

protected:
    void run()
    {
        for(int i = 0; i < 10000; ++i){
            qDebug() << "L";
                samples->reload();
            qDebug() << "K";
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
        Samples* samples = new Samples();
        Loader* loader = new Loader(samples);
        Woodpecker* woodpecker = new Woodpecker(samples);
            loader->start();
            woodpecker->start();
    return a.exec();
}
