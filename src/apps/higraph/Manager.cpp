#include "Manager.h"

#include "SamplesManager.h"
#include <QQmlContext>
#include <QTimer>
Manager::Manager(QObject* root, QObject *parent) :
    QObject(parent),
    firstFileWasLoaded(false),
    root(root)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(moveAllFurther()));

    samplesManager = new SamplesManager(this);
    connect(samplesManager, SIGNAL(haveBeenLoaded(int)), SLOT(haveBeenLoaded(int)));

    findObjects();


    connect(starter, SIGNAL(start()), SLOT(start()));
    connect(starter, SIGNAL(pause()), timer, SLOT(stop()));
    connect(mover, SIGNAL(valueChanged()), SLOT(moveAllToMoverPos()));
    connect(root, SIGNAL(pathsArePrepared()), SLOT(loadData()));
    connect(root, SIGNAL(closeAllFiles()), samplesManager, SLOT(clear()));
    connect(root, SIGNAL(closeAllFiles()), SLOT(resetFileLoadingFlag()));
}


QObject* Manager::findObject(QObject* parent, const QString& childName)
{
    return parent->findChild<QObject*>(childName);
}

void Manager::findObjects()
{
    menu = findObject(root, "menu");
        starter = findObject(menu, "starter");
    windowsModel = findObject(root, "windowsModel");
        histogram = findObject(windowsModel, "histogram");
            mover = findObject(histogram, "mover");
            sliceTime = findObject(histogram, "sliceTime");
            numberSliceMaxValue = findObject(histogram, "numberSliceMaxValue");
            sliceMaxValue = findObject(histogram, "sliceMaxValue");
            sliceAverage = findObject(histogram, "sliceAverage");
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
#include <Samples.h>
void Manager::haveBeenLoaded(int i)
{
    if(!firstFileWasLoaded){
        const int currentSize = samplesManager->getSamples(i)->height();
        if(currentSize >= 2){
            mover->setProperty("maximumValue",currentSize - 2);
        }
    }
    if(i == 0){
        firstFileWasLoaded = true;
    }
    //j == 0 is time
    for(int j = 1; j < samplesManager->getSamples(i)->count(); ++j){
        QMetaObject::invokeMethod(
            histogram,
            "append"
        );
    }

    moveAllToMoverPos();
}

#include <QString>
static QString reduce(double value)
{
    QStringList digits = QString("%1").arg(value).split(".");
    if(digits.size() > 1){
        digits[1].remove(3, digits[1].size() - 3);
        return digits[0] + "." + digits[1];
    }
    else{
        return digits[0];
    }
}

void Manager::moveAllToMoverPos()
{
    const int moverPos = mover->property("value").toInt();
    if(!samplesManager->count() || !samplesManager->getSamples(0)->count()){
        sliceTime->setProperty("text", 0);
    }
    else{
        const QVector<double>& values = samplesManager->getSamples(0)->getColumn(0);
        if(moverPos < values.size()){
            sliceTime->setProperty("text", "Время: " + reduce(values[moverPos]));
        }
    }
    move(moverPos);
}

void Manager::move(int pos)
{
    int modelIndex = 0;
    int maxValueIndex = 0;
    double average = 0;
    //iColumn == 0 is time
    double maxValue = 0;
    for(int filesCounter = 0; filesCounter < samplesManager->count(); ++filesCounter){
         for(int iColumn = 1; iColumn < samplesManager->getSamples(filesCounter)->count(); ++iColumn){
            const QVector<double> values = samplesManager->getSamples(filesCounter)->getColumn(iColumn);
            double value = values.size() <= pos ? 0 : values.at(pos);
            average += value;
            if(value > maxValue){
                maxValue = value;
                maxValueIndex = modelIndex + 1;
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

    numberSliceMaxValue->setProperty("text", QString("Номер максимального: %1").arg(maxValueIndex));
    sliceMaxValue->setProperty("text", "Максимальный: " + reduce(maxValue));
    sliceAverage->setProperty("text", "Среднее: " + reduce(modelIndex ? average / modelIndex : 0));
}

void Manager::start()
{
    timer->start(COUNT_MS_FOR_UPDATING);
}

void Manager::moveAllFurther()
{
    const int moverPos = mover->property("value").toInt();
    mover->setProperty("value", moverPos + 1);

    const int maxPos = mover->property("maximumValue").toInt();
    if(moverPos == maxPos){
        timer->stop();
        QMetaObject::invokeMethod(starter, "stop");
    }
}
