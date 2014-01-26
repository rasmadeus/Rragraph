#include "Samples.h"

class SamplesLoader;
#include <QMutex>
#include <QVector>
#include <QMutexLocker>
#include <QStringList>
class SamplesPrivateData
{
public:
    mutable QMutex locker;
    QVector<QVector<double>> columns;
    QStringList headers;
    QString pathToSrc;
    SamplesLoader* loader;
    QStringList proxyHeaders;
    double proxyColumnAddend;
    double proxyColumnMult;

    SamplesPrivateData();
    ~SamplesPrivateData();

    inline void pushBackColumnsValue(int i, double value)
    {
        columns[i].push_back(value);
    }

    inline bool proxyScaleIsEmpty() const
    {
        return proxyColumnAddend == 0 && proxyColumnMult == 1;
    }

    QVector<double> getProxyColumn(int i) const
    {
        QVector<double> res;
        std::transform(
            columns[i].begin(),
            columns[i].end(),
            std::back_inserter(res),
            [this](double value){return proxyColumnMult * value + proxyColumnAddend;}
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
        QRegExp rx("(\"[^\"]+\"|\\S+)");
        int pos = 0;
        while((pos = rx.indexIn(headers, pos)) != -1){
            QString header = rx.cap(1);
            removeQuotes(header);
            d->headers.push_back(header);
            d->proxyHeaders.push_back(header);
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
            QStringList column = rawDataStreamer
                .readLine()
                .simplified()
                .replace(",", ".")
                .split(" ");
            if(column.isEmpty()){
                continue;
            }
            rearrange(column);
            for(int i = 0; i < d->headers.size(); ++i){
                d->pushBackColumnsValue(i, column[i].toDouble());
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

SamplesPrivateData::SamplesPrivateData():
    proxyColumnAddend(0),
    proxyColumnMult(1)
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
    QMutexLocker locker(&d->locker);
    return d->headers.count();
}

int Samples::height() const
{
    QMutexLocker locker(&d->locker);
    return d->columns.isEmpty() ? 0 : d->columns[0].size();
}

const QString& Samples::getPathToSrc() const
{
    QMutexLocker locker(&d->locker);
    return d->pathToSrc;
}

QFileInfo Samples::getPathSrcFileInfo() const
{
    QMutexLocker locker(&d->locker);
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

QStringList Samples::getProxyHeaders() const
{
    QMutexLocker locker(&d->locker);
    return d->proxyHeaders;
}

void Samples::setProxyHeader(const QString& header, int i)
{
    QMutexLocker locker(&d->locker);
    d->proxyHeaders[i] = header;
}

QVector<double> Samples::getProxyColumn(int i) const
{
    QMutexLocker locker(&d->locker);
    return d->proxyScaleIsEmpty() ? d->columns[i] : d->getProxyColumn(i);
}

void Samples::setProxyColumnAddend(double addend)
{
    QMutexLocker locker(&d->locker);
    d->proxyColumnAddend = addend;
}

void Samples::setProxyColumnMult(double mult)
{
    QMutexLocker locker(&d->locker);
    d->proxyColumnMult = mult;
}

void Samples::resetProxyHeaders()
{
    QMutexLocker locker(&d->locker);
    d->proxyHeaders = d->headers;
}
