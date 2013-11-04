#include "Files.h"

SINGLETON_IMPLEMENTATION(Files)

Files::Files(QObject* parent) :
    QObject(parent),
    lastLoadedFilePath("Files/lastLoadedFilePath")
{
}

#include <QSettings>
Files::~Files()
{
    qDeleteAll(loaders);
    qDeleteAll(samples);   
}

void Files::load(const QStringList& paths)
{
    foreach(const QString& path, paths){
        Samples* sample = new Samples(path);
        Loader* loader = new Loader(sample, this);
        connect(loader, SIGNAL(wasLoaded(Samples*)), SLOT(wasLoaded(Samples*)));
        connect(loader, SIGNAL(headersWasParsed(Samples*)), SLOT(headersWasParsed(Samples*)));
        samples << sample;
        loaders << loader;
        emit wasAdded(samples.size() - 1);
        loader->start();
    }
    if(!paths.isEmpty()){
        lastLoadedFilePath = paths.last();
    }
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

const QVector<qreal> &Files::getSamples(int iFile, int i) const{
    return samples[iFile]->getSamples()[i];
}

const QStringList& Files::getHeaders(int iFile) const{
    return samples[iFile]->getHeaders();
}

int Files::countSamples(int iFile) const{
    return samples[iFile]->getSamples().size();
}


int Files::countSamples() const{
    return samples.size();
}

QFileInfo Files::getPath(int iFile) const{
    return samples[iFile]->getPath();
}

QString Files::getLastLoadedFilePath(){
    return lastLoadedFilePath();
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

void Files::wasLoaded(Samples* samples){
    emit wasLoaded(this->samples.indexOf(samples));
}

void Files::headersWasParsed(Samples* samples){
    emit headersWasParsed(this->samples.indexOf(samples));
}

bool Files::isLoading(int iFile) const{
    return loaders[iFile]->isRunning();
}
