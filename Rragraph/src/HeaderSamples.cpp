#include "HeaderSamples.h"

SINGLETON_IMPLEMENTATION(HeaderSamples)

#include "Files.h"
HeaderSamples::HeaderSamples(QObject *parent) :
    QObject(parent)
{
    connect(Files::getInstance(), SIGNAL(wasAdded(int)), SLOT(wasAdded(int)));
    connect(Files::getInstance(), SIGNAL(wasRemoved(int)), SLOT(wasRemoved(int)));
}

int HeaderSamples::size(int iFile) const{
    return iFile < 0 || iFile >= samples.size() ? 0 : samples[iFile].size();
}

const QString& HeaderSamples::getHeader(int iFile, int i) const{
    return samples[iFile][i];
}

void HeaderSamples::setHeader(int iFile, int i, const QString& header){
    samples[iFile][i] = header;
    emit headerWasChanged(iFile, i, header);
}

void HeaderSamples::reset(int iFile){
    samples[iFile] = Files::getInstance()->getHeaders(iFile);
    for(int i = 0; i < samples[iFile].size(); ++i){
        emit headerWasChanged(iFile, i, samples[iFile][i]);
    }
}

void HeaderSamples::wasAdded(int iFile){
    samples << Files::getInstance()->getHeaders(iFile);
}

void HeaderSamples::wasRemoved(int iFile){
    samples.remove(iFile);
}
