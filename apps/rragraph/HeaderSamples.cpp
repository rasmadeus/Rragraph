#include "HeaderSamples.h"

SINGLETON_IMPLEMENTATION(HeaderSamples, QObject)

#include "Files.h"
HeaderSamples::HeaderSamples(QObject* parent) :
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

void HeaderSamples::wasAdded(int iFile){
    samples << Files::getInstance()->getHeaders(iFile);
}

void HeaderSamples::wasRemoved(int iFile){
    samples.remove(iFile);
}

void HeaderSamples::setHeader(int iFile, int i, const QString& header){
    samples[iFile][i] = header;
    emit headerWasChanged(iFile, i, header);
}

#include <exception>
void HeaderSamples::reset(int iFile){
    try{
        samples[iFile] = Files::getInstance()->getHeaders(iFile);
    }
    catch(std::exception& er){
        return;
    }

    for(int i = 0; i < samples[iFile].size(); ++i){
        emit headerWasChanged(iFile, i, samples[iFile][i]);
    }
}

#include <QJsonArray>
#include <QJsonObject>
void HeaderSamples::serialize(QJsonObject& root) const
{
    QJsonObject headers;
    for(int iFile = 0; iFile < samples.size(); ++iFile){
        QJsonObject difference;
        const QStringList& native = Files::getInstance()->getHeaders(iFile);
        const QStringList& current = samples[iFile];
        for(int i = 0; i < native.size(); ++i){
            if(native[i] != current[i]){
                difference[QString("%1").arg(i)] = current[i];
            }
        }
        if(!difference.isEmpty()){
            headers[QString("%1").arg(iFile)] = difference;
        }
    }
    root["headers"] = headers;
}

void HeaderSamples::restore(int iFile, const QJsonObject& root)
{
    const QJsonObject headers = root.value("headers").toObject();
    foreach(const QString& key, headers.keys()){
        if(iFile == key.toInt()){
            const QJsonObject difference = headers.value(key).toObject();
            foreach(const QString& key, difference.keys()){
                const int i = key.toInt();
                if(Files::getInstance()->isOutOfRange(iFile, i)){
                    return;
                }
                const QString& native = Files::getInstance()->getHeaders(iFile)[i];
                setHeader(iFile, i, difference.value(key).toString(native));
            }
            return;
        }
    }
}
