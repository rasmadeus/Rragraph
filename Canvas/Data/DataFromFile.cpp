#include "DataFromFile.h"

DataFromFile::DataFromFile(QObject* parent):
    QObject(parent),
    readerFile(this)
{
    connect(&readerFile, SIGNAL(dataWasLoaded(DataFromFile*)),  this, SIGNAL(dataWasLoaded(DataFromFile*)));
    connect(&readerFile, SIGNAL(deleteMePlease()), this, SLOT(destroy()));
}

void DataFromFile::destroy()
{
    stopLoadData();
    delete this;
}

//Filling the _data_from_file.
void DataFromFile::loadData(QString path)
{
    if(!dataFromFile.isEmpty()) dataFromFile.clear();
    pathToFile = path;
    readerFile.start();
}

//If the first row of text file, is (for example)
// "H e a der 1" Header2    Header_3 then
//it will be created 3 Columns.
#include <QRegExp>
void DataFromFile::createHeaders(QString firstRow)
{
    QRegExp regExp("(\"[^\"]*\"|\\S+)");
    int pos = 0;
    while ((pos = regExp.indexIn(firstRow, pos)) != -1) {
        dataFromFile.push_back(Column(regExp.cap(1).replace(QRegExp("\""), "")));
        pos += regExp.matchedLength();
    }
}

//Parsing row into float values.
#include <QStringList>
void DataFromFile::pushBackValues(QString row)
{
    QStringList values = row.simplified().split(" ");
    int needItem = dataFromFile.size() - values.size();
    for(int i=0; i<needItem; ++i) values.push_back("0");
    for(int i=0; i<dataFromFile.size(); ++i) dataFromFile[i].pushBackValue(values[i].toFloat());
}

QString DataFromFile::getPathToFile() const
{
    return pathToFile;
}

#include <QFileInfo>
QString DataFromFile::getFileName() const
{
    return QFileInfo(pathToFile).fileName();
}

void DataFromFile::stopLoadData()
{
    if(readerFile.isRunning()) readerFile.terminate();
}

#include "../Model/Columns.h"
void DataFromFile::createDynamicColumns(Columns *columns)
{
    foreach(const Column& column, dataFromFile){
        columns->pushBack(column.getHeader());
    }
}

#include "../Model/DynamicColumn.h"
void DataFromFile::replaceDynamicColumns(QVector<DynamicColumn*>& columns)
{
    int countDifItem = dataFromFile.size() - columns.size();
    //Add necessary elements
    if(countDifItem > 0){
        for(int i=columns.size(); i<dataFromFile.size(); ++i) columns.push_back(new DynamicColumn(dataFromFile[i].getHeader()));
    }
    //Remove unnecessary elements
    if(countDifItem < 0){
        for(int i=dataFromFile.size(); i<columns.size(); ++i) delete columns[i];
        columns.remove(dataFromFile.size(), - countDifItem);
    }
    //Set native names for columns
    for(int i=0; i<columns.size(); ++i){
        columns[i]->header = dataFromFile[i].getHeader();
    }
}

#include "../Curves/PlotCurve.h"
PlotCurve *DataFromFile::getCurve(int iX, int iY, const DynamicColumn *col) const
{
    return new PlotCurve(
        col->getHeader(),
        col->style,
        dataFromFile[iX].getValues(),
        col->isOne() ? dataFromFile[iY].getValues() : dataFromFile[iY].getValues(col->mult)
    );
}

void DataFromFile::fill(PlotCurve* curve, int iX, int iY, float mult) const
{
    curve->setSamples(
        dataFromFile[iX].getValues(),
        mult == 1 ? dataFromFile[iY].getValues() : dataFromFile[iY].getValues(mult)
    );
}
