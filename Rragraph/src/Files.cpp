#include "Files.h"

SINGLETON_IMPLEMENTATION(Files, QObject)

Files::Files(QObject* parent) :
    QObject(parent),
    lastLoadedFilePath("Files/lastLoadedFilePath")
{
}
#include <QDebug>
#include <QSettings>
Files::~Files()
{
    qDeleteAll(loaders);
    qDeleteAll(samples);   
}

const QVector<qreal> &Files::getSamples(int iFile, int i) const{
    return samples[iFile]->getSamples()[i];
}

#include <stdexcept>
const QStringList& Files::getHeaders(int iFile) const{
    if(iFile < 0 || iFile >= samples.size()){
        throw std::out_of_range("out of range");
    }
    return samples[iFile]->getHeaders();
}

int Files::countSamples(int iFile) const{
    return samples[iFile]->getSamples().size();
}

int Files::countSamples() const{
    return samples.size();
}

#include <QFileInfo>
QFileInfo Files::getPath(int iFile) const{
    return samples[iFile]->getPath();
}

QString Files::getLastLoadedFilePath(){
    return lastLoadedFilePath();
}

void Files::wasLoaded(Samples* samples){
    emit wasLoaded(this->samples.indexOf(samples));
}

void Files::headersWasParsed(Samples* samples){
    emit headersWasParsed(this->samples.indexOf(samples));
}

bool Files::isLoading(int iFile) const{
    return loaders[iFile]->isRunning();
}

bool Files::isOutOfRange(int iFile) const{
    return iFile < 0 || iFile >= countSamples() ? true : false;
}

bool Files::isOutOfRange(int iFile, int i) const{
    return i < 0 || i >= countSamples(iFile) ? true : false;
}

void Files::load(const QStringList& paths)
{
    foreach(const QString& path, paths){
        if(!QFileInfo(path).exists()){
            continue;
        }
        Samples* sample = new Samples(path);
        Loader* loader = new Loader(sample, this);
        connect(loader, SIGNAL(wasLoaded(Samples*)), SLOT(wasLoaded(Samples*)));
        connect(loader, SIGNAL(headersWasParsed(Samples*)), SLOT(headersWasParsed(Samples*)));
        samples.push_back(sample);
        loaders.push_back(loader);
        emit wasAdded(samples.size() - 1);
        loader->start();
    }
    if(!paths.isEmpty()){
        lastLoadedFilePath = paths.last();
    }
}

void Files::removeAll()
{    
    while(!samples.isEmpty()){
        remove(0);
    }
    emit wasRemovedAll();
}

void Files::remove(int iFile)
{
    Samples* sample = samples[iFile];
    Loader* loader = loaders[iFile];    
    loaders.remove(iFile);
    samples.remove(iFile);
    delete loader;
    delete sample;
    emit wasRemoved(iFile);
}

void Files::reload(int iFile, const QString& path)
{
    samples[iFile]->setPath(path);
    if(loaders[iFile]->isRunning()){
        loaders[iFile]->terminate();
        while(loaders[iFile]->isRunning());
    }
    loaders[iFile]->start();
    lastLoadedFilePath = path;
}

#include <QFileDialog>
void Files::reload(int iFile)
{
    if(iFile < 0 || iFile >= samples.size()){
        load();
        return;
    }
    QString path = QFileDialog::getOpenFileName(
        static_cast<QWidget*>(parent()),
        tr("Select file, which you want to load"),
        lastLoadedFilePath()
    );
    if(!path.isEmpty()){
        reload(iFile, path);
    }
}
#include <QDebug>
#include "Project.h"
QString Files::getRelativePath(int iFile) const{
    const QString projectPath = Project::getInstance()->getPath().getPath();

    if(projectPath.isEmpty()){
        return getPath(iFile).fileName();
    }

    const QString filePath = getPath(iFile).absoluteFilePath();
    const QDir projectDir = Project::getInstance()->getProjectDir();

    return projectDir.relativeFilePath(filePath);
}


void Files::load()
{
    QStringList paths = QFileDialog::getOpenFileNames(
        static_cast<QWidget*>(parent()),
        tr("Load raw files to project"),
        getLastLoadedFilePath()
    );
    if(!paths.isEmpty()){
        load(paths);
    }
}

#include "Project.h"
#include <QJsonArray>
#include <QJsonObject>
void Files::serialize(QJsonObject& root)
{
    const QDir projectDir = Project::getInstance()->getProjectDir();
    QJsonArray files;
    foreach (Samples* sample, samples) {
       const QString  filePath = sample->getPath().absoluteFilePath();
       files.push_back(projectDir.relativeFilePath(filePath));
    }
    root["files"] = files;
}

void Files::restore(QJsonObject& root)
{
    const QDir projectDir = Project::getInstance()->getProjectDir();
    QStringList paths;
    foreach(const QJsonValue& value, root.value("files").toArray()){
        paths << projectDir.absoluteFilePath(value.toString());
    }
    load(paths);
}
