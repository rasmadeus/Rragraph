#include "Manager.h"

#include "SamplesManager.h"
#include <QQmlContext>
Manager::Manager(QQmlContext* rootContext, QObject* root, QObject *parent) :
    QObject(parent),
    rootContext(rootContext),
    root(root)
{
    samplesManager = new SamplesManager(this);
    connect(samplesManager, SIGNAL(haveBeenLoaded(int)), SLOT(haveBeenLoaded(int)));

    windowsModel = root->findChild<QObject*>("windowsModel");
    if(windowsModel){
        histogram = windowsModel->findChild<QObject*>("histogram");
        if(histogram){
            mover = histogram->findChild<QObject*>("mover");
        }
    }

    connect(root, SIGNAL(pathsArePrepared()), SLOT(loadData()));
    connect(root, SIGNAL(closeAllFiles()), samplesManager, SLOT(clear()));
    connect(histogram, SIGNAL(moverPosWasChanged()), SLOT(moveAllToMoverPos()));
}

#include <QDebug>
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
    const int maxSize = mover->property("maximumValue").toInt();
    const int currentSize = samplesManager->height(i);
    if(currentSize > maxSize){
        mover->setProperty("maximumValue", currentSize - 1);
    }
    //j == 0 is time
    for(int j = 1; j < samplesManager->countSamples(i); ++j){
        QMetaObject::invokeMethod(
            histogram,
            "append"
        );
    }
}

void Manager::moveAllToMoverPos()
{
    const int moverPos = mover->property("value").toInt();
    move(moverPos);
}

void Manager::move(int pos)
{
    int modelIndex = 0;
    //iColumn == 0 is time

    for(int filesCounter = 0; filesCounter < samplesManager->count(); ++filesCounter){
        for(int iColumn = 1; iColumn < samplesManager->countSamples(filesCounter); ++iColumn){
            const QVector<double> values = samplesManager->getColumnSamples(filesCounter, iColumn);
            double value = values.size() <= pos ? 0 : values.at(pos);
            QMetaObject::invokeMethod(
                histogram,
                "setValue",
                Q_ARG(QVariant, modelIndex),
                Q_ARG(QVariant, value)
            );
            ++modelIndex;
        }
    }

}
