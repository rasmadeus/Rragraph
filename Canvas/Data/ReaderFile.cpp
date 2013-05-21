#include "ReaderFile.h"
#include "Column.h"
#include "DataFromFile.h"

ReaderFile::ReaderFile(DataFromFile* dataFromFile, QObject *parent) :
    QThread(parent),
    dataFromFile(dataFromFile)
{
}

#include <QFile>
#include <QTextStream>
void ReaderFile::run()
{
    QFile file(dataFromFile->getPathToFile());
    if(!file.open(QFile::ReadOnly)){
        emit deleteMePlease();
        return;
    }
    QTextStream in(&file);
        dataFromFile->createHeaders(in.readLine());
        while(!in.atEnd()) dataFromFile->pushBackValues(in.readLine());
    file.close();
    emit dataWasLoaded(dataFromFile);
}
