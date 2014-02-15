#include "Samples.h"

class SamplesLoader;
#include <QMutex>
#include <QVector>
#include <QMutexLocker>
#include <QStringList>
#include <QHash>
class SamplesPrivateData
{
public:
    mutable QMutex locker;
    QVector<QVector<double>> columns;
    QStringList headers;
    QString pathToSrc;
    SamplesLoader* loader;
    QHash<int, QString> proxyHeaders;
    QHash<int, double> proxyColumnsAddend;
    QHash<int, double> proxyColumnsMult;

    SamplesPrivateData();
    ~SamplesPrivateData();

    inline void pushBackColumnsValue(int i, double value)
    {
        columns[i].push_back(value);
    }

    inline bool proxyScaleIsEmpty(int i) const
    {
        return !(proxyColumnsMult.contains(i) || proxyColumnsAddend.contains(i));
    }

    QVector<double> getProxyColumn(int i) const
    {
        QVector<double> res;
        std::transform(
            columns[i].begin(),
            columns[i].end(),
            std::back_inserter(res),
            [this, i](double value){
                const double mult = proxyColumnsMult.contains(i) ? proxyColumnsMult[i] : 1;
                const double addend = proxyColumnsAddend.contains(i) ? proxyColumnsAddend[i] : 0;
                return mult * value + addend;
            }
        );
        return res;
    }
};

#include <QThread>
#include <QFile>
#include <QTextStream>
class SamplesLoader: public QThread
{
public:
    explicit SamplesLoader(SamplesPrivateData* d, QObject* parent = 0):
        QThread(parent),
        d(d),
        stopCrane(true)
    {
    }

    ~SamplesLoader()
    {
        stop();
    }

    inline void stop()
    {
        stopCrane = true;
        while(isRunning());
    }

protected:
    void run()
    {
        stopCrane = false;
        QFile rawData(d->pathToSrc);
        if(rawData.open(QFile::ReadOnly)){
            d->locker.lock();
                QTextStream rawDataStreamer(&rawData);
                createHeaders(rawDataStreamer.readLine());
                createColumns(rawDataStreamer);
            d->locker.unlock();
        }
        stopCrane = true;
    }

private:
    inline void createHeaders(QString headers)
    {
        d->headers.clear();
        d->columns.clear();
        d->proxyHeaders.clear();
        d->proxyColumnsAddend.clear();
        d->proxyColumnsMult.clear();
        QRegExp rx("(\"[^\"]+\"|\\S+)");
        int pos = 0;
        while((pos = rx.indexIn(headers, pos)) != -1){
            QString header = rx.cap(1);
            removeQuotes(header);
            d->headers.push_back(header);
            d->columns.push_back(QVector<double>());
            pos += rx.matchedLength();
        }
    }

    inline void removeQuotes(QString& header)
    {
        if(header.size() > 2){
            if(std::find(header.begin()+1, header.end()-1, '"') != (header.end())){
                header.replace("\"", "");
            }
        }
    }

    inline void createColumns(QTextStream& rawDataStreamer)
    {
        while(!(rawDataStreamer.atEnd() || stopCrane)){
            QString line = rawDataStreamer.readLine().simplified();
            if(!line.isEmpty()){
                QStringList column = line.replace(",", ".").split(" ");
                rearrange(column);
                for(int i = 0; i < d->headers.size(); ++i){
                    d->pushBackColumnsValue(i, column[i].toDouble());
                }
            }
        }
    }

    inline void rearrange(QStringList& column)
    {
        while(column.size() < d->headers.size()){
            column << "0";
        }
    }

    SamplesPrivateData* d;
    bool stopCrane;
};

SamplesPrivateData::SamplesPrivateData()
{
    loader = new SamplesLoader(this);
}

SamplesPrivateData::~SamplesPrivateData()
{
    delete loader;
}

Samples::Samples(QObject *parent) :
    QObject(parent)
{
    d = new SamplesPrivateData();
    connect(d->loader, SIGNAL(finished()), SIGNAL(haveBeenLoaded()));
    connect(d->loader, SIGNAL(finished()), SLOT(samplesHaveBeenLoaded()));
}

Samples::~Samples()
{
    delete d;
}

const QStringList& Samples::getHeaders() const
{
    QMutexLocker locker(&d->locker);
    return d->headers;
}

const QVector<double>& Samples::getColumn(int i) const
{
    QMutexLocker locker(&d->locker);
    return d->columns[i];
}

int Samples::count() const
{
    return d->headers.count();
}

int Samples::height() const
{
    QMutexLocker locker(&d->locker);
    return d->columns.isEmpty() ? 0 : d->columns[0].size();
}

const QString& Samples::getPathToSrc() const
{
     return d->pathToSrc;
}

QFileInfo Samples::getPathSrcFileInfo() const
{
    return QFileInfo(d->pathToSrc);
}

void Samples::load(const QString& pathToSrc)
{
    d->pathToSrc = pathToSrc;
    reload();
}

void Samples::reload()
{
    if(d->loader->isRunning()){
        d->loader->stop();
    }
    d->loader->start();
}

void Samples::samplesHaveBeenLoaded()
{
    emit haveBeenLoaded(this);
}

bool Samples::isLoading() const
{
    return d->loader->isRunning();
}

void Samples::waitLoading() const
{
    while(isLoading());
}

const QString& Samples::getProxyHeader(int i) const
{
    return d->proxyHeaders.contains(i) ? d->proxyHeaders[i] : d->headers[i];
}

void Samples::setProxyHeader(const QString& header, int i)
{
    if(header != d->headers[i]){
        d->proxyHeaders[i] = header;
    }
    else{
        d->proxyHeaders.take(i);
    }
    emit proxyDataWasChanged();
}

QVector<double> Samples::getProxyColumn(int i) const
{
    return d->proxyScaleIsEmpty(i) ? d->columns[i] : d->getProxyColumn(i);
}

double Samples::getProxyColumnAddend(int i) const
{
    return d->proxyColumnsAddend.contains(i) ? d->proxyColumnsAddend[i] : 0;
}

double Samples::getProxyColumnMult(int i) const
{
    return d->proxyColumnsMult.contains(i) ? d->proxyColumnsMult[i] : 1;
}

void Samples::setProxyColumnAddend(double addend, int i)
{
    if(addend){
        d->proxyColumnsAddend[i] = addend;
    }
    else{
        d->proxyColumnsAddend.take(i);
    }
    emit proxyDataWasChanged();
}

void Samples::setProxyColumnMult(double mult, int i)
{
    if(mult != 1){
        d->proxyColumnsMult[i] = mult;
    }
    else{
        d->proxyColumnsMult.take(i);
    }
    emit proxyDataWasChanged();
}

void Samples::resetProxyHeaders()
{
    d->proxyHeaders.clear();
    emit proxyDataWasChanged();
}

void Samples::resetProxyMult()
{
    d->proxyColumnsMult.clear();
    emit proxyDataWasChanged();
}

void Samples::resetProxyAddend()
{
    d->proxyColumnsAddend.clear();
    emit proxyDataWasChanged();
}
