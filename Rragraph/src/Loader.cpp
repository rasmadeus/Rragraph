#include "Loader.h"

Loader::Loader(Samples* samples, QObject *parent) :
    QThread(parent),
    samples(samples)
{
}

Loader::~Loader()
{
    if(isRunning()){
        terminate();
        while(isRunning());
    }
}

#include <QFile>
#include <QTextStream>
#include "Samples.h"
#include <QFileInfo>
void Loader::run()
{    
    QFile file(samples->getPath().absoluteFilePath());
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    samples->clear();

    QTextStream fileReader(&file);

    fillHeaders(fileReader.readLine());
    while(!fileReader.atEnd()){
        append(fileReader.readLine());
    }

    emit wasLoaded(samples);
}

static void removeQuotes(QString& header)
{
    if(header.size() > 2){
        if(std::find(header.begin()+1, header.end()-1, '"') != (header.end())){
            header.replace("\"", "");
        }
    }
}

void Loader::fillHeaders(const QString& firstRow)
{
    QRegExp rx("(\"[^\"]+\"|\\S+)");
    int pos = 0;
    while((pos = rx.indexIn(firstRow, pos)) != -1){
        QString header = rx.cap(1);
        removeQuotes(header);
        samples->pushBack(header);
        pos += rx.matchedLength();
    }
    emit headersWasParsed(samples);
}

void Loader::rearrange(QStringList& column)
{
    while(column.size() < samples->getHeaders().size()){
        column << "0";
    }
}

void Loader::append(const QString& row)
{
    QString simplifiedRow = row.simplified();
    if(simplifiedRow.isEmpty()){
        return;
    }
    QStringList column = simplifiedRow.split(" ");
    rearrange(column);
    for(int i = 0; i < samples->getHeaders().size(); ++i){
        samples->pushBack(i, column[i].toDouble());
    }
}


