#include "Samples.h"

Samples::Samples(const QString& path):
    path(path)
{
}

void Samples::pushBack(const QString& header){
    headers << header;
    if(samples.size() < headers.size()){
        samples << QVector<qreal>();
    }
}

void Samples::pushBack(int i, qreal sample){
    samples[i] << sample;
}

const QStringList& Samples::getHeaders() const{
    return headers;
}

const QVector<QVector<qreal> > Samples::getSamples() const{
    return samples;
}

void Samples::setPath(const QString& path){
    this->path = path;
}

#include <QFileInfo>
QFileInfo Samples::getPath() const{
    return QFileInfo(path);
}

void Samples::clear()
{
    headers.clear();
    samples.clear();
}
