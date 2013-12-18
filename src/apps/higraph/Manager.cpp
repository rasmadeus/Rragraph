#include "Manager.h"

#include "SamplesManager.h"
#include "SamplesQListModel.h"
#include <QQmlContext>
Manager::Manager(QQmlContext* rootContext, QObject* root, QObject *parent) :
    QObject(parent),
    rootContext(rootContext),
    root(root),
    data(nullptr)
{
    samplesManager = new SamplesManager(this);
    samplesModel = new SamplesQListModel(this);
    samplesModel->setSamplesManager(samplesManager);
    rootContext->setContextProperty("filesModel", samplesModel);
    windowsModel = root->findChild<QObject*>("windowsModel");
    if(windowsModel){
        data = windowsModel->findChild<QObject*>("data");
        if(data){
            connect(data, SIGNAL(pathsArePrepared()), SLOT(loadData()));
        }
    }    
}

#include <QUrl>
#include <QVariant>
void Manager::loadData()
{
    QVariant urls;
    QMetaObject::invokeMethod(data, "getUrls", Q_RETURN_ARG(QVariant, urls));

    QList<QUrl> pathsToSrc = urls.value<QList<QUrl>>();
    foreach(const QUrl& url, pathsToSrc){
        samplesManager->append(url.toLocalFile());
    }
}
