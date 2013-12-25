#include "Manager.h"

#include "SamplesManager.h"
#include <QQmlContext>
#include <QTimer>
Manager::Manager(QQmlContext* rootContext, QObject* root, QObject *parent) :
    QObject(parent),
    firstFileWasLoaded(false),
    rootContext(rootContext),
    root(root)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(incAll()));

    samplesManager = new SamplesManager(this);
    connect(samplesManager, SIGNAL(haveBeenLoaded(int)), SLOT(haveBeenLoaded(int)));

    windowsModel = root->findChild<QObject*>("windowsModel");
    if(windowsModel){
        histogram = windowsModel->findChild<QObject*>("histogram");
        if(histogram){
            mover = histogram->findChild<QObject*>("mover");
            connect(mover, SIGNAL(valueChanged()), SLOT(moveAllToMoverPos()));

            starter = histogram->findChild<QObject*>("starter");
            connect(starter, SIGNAL(start()), SLOT(start()));
            connect(starter, SIGNAL(pause()), timer, SLOT(stop()));

            firstFileTime = histogram->findChild<QObject*>("firstFileTime");
            sliceMaxValue = histogram->findChild<QObject*>("sliceMaxValue");
        }
    }

    connect(root, SIGNAL(pathsArePrepared()), SLOT(loadData()));
    connect(root, SIGNAL(closeAllFiles()), samplesManager, SLOT(clear()));
    connect(root, SIGNAL(closeAllFiles()), SLOT(resetFileLoadingFlag()));
}

void Manager::resetFileLoadingFlag()
{
    firstFileWasLoaded = false;
}

#include <QUrl>
#include <QVariant>
void Manager::loadData()
{
    QVariant urls;
    QMetaObject::invokeMethod(root, "getUrls", Q_RETURN_ARG(QVariant, urls));

    QList<QUrl> pathsToSrc = urls.value<QList<QUrl>>();
    foreach(const QUrl& url, pathsToSrc){
        samplesManager->append(url.toLocalFile());
    }
}

#include <QColor>
#include <algorithm>
void Manager::haveBeenLoaded(int i)
{
    if(!firstFileWasLoaded){
        const int currentSize = samplesManager->height(i);
        mover->setProperty("maximumValue", currentSize - 2);
    }
    if(i == 0){
        firstFileWasLoaded = true;
    }
    //j == 0 is time
    for(int j = 1; j < samplesManager->countSamples(i); ++j){
        QMetaObject::invokeMethod(
            histogram,
            "append"
        );
    }
    if(samplesManager->count() == 1){
        moveAllToMoverPos();
    }
}

void Manager::moveAllToMoverPos()
{
    const int moverPos = mover->property("value").toInt();
    if(!samplesManager->count() || !samplesManager->countSamples(0)){
        firstFileTime->setProperty("currentFileTime", 0);
    }
    else{
        firstFileTime->setProperty("currentFileTime", samplesManager->getColumnSamples(0, 0)[moverPos]);
    }

    move(moverPos);
}

#include <algorithm>
void Manager::move(int pos)
{
    int modelIndex = 0;
    //iColumn == 0 is time
    double maxValue = 0;
    for(int filesCounter = 0; filesCounter < samplesManager->count(); ++filesCounter){
        for(int iColumn = 1; iColumn < samplesManager->countSamples(filesCounter); ++iColumn){
            const QVector<double> values = samplesManager->getColumnSamples(filesCounter, iColumn);
            double value = values.size() <= pos ? 0 : values.at(pos);
            if(value > maxValue){
                maxValue = value;
            }
            QMetaObject::invokeMethod(
                histogram,
                "setValue",
                Q_ARG(QVariant, modelIndex),
                Q_ARG(QVariant, value)
            );
            ++modelIndex;
        }
    }
    sliceMaxValue->setProperty("currentSliceMaxValue", maxValue);
}

void Manager::start()
{
    timer->start(150);
}

void Manager::incAll()
{
    const int moverPos = mover->property("value").toInt();
    mover->setProperty("value", moverPos + 1);

    const int maxPos = mover->property("maximumValue").toInt();
    if(moverPos == maxPos){
        timer->stop();
        QMetaObject::invokeMethod(starter, "stop");
    }
}
