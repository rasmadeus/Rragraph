#include "Columns.h"
#include <QString>
#include "../Data/DataFromFile.h"
#include "DynamicColumn.h"

Columns::Columns(DataFromFile* dataFromFile, Canvas *canvas):
    abscissRow(0),
    dataFromFile(dataFromFile),
    canvas(canvas)
{
    dataFromFile->createDynamicColumns(this);
}

#include "../Curves/PlotCurve.h"
#include "../Canvas.h"
Columns::~Columns()
{
    qDeleteAll(columns);
}

void Columns::detach()
{
    foreach(int key, ordinates.keys())
        delete ordinates.take(key);
    canvas->replot();
}


//Push back a new DynamicColumn into _columns.
void Columns::pushBack(QString header)
{
    columns.push_back(new DynamicColumn(header));
}

//The _columns's size.
int Columns::row() const{
    return columns.size();
}

#include "../Curves/PlotCurve.h"
#include "../Canvas.h"
void Columns::setMult(int row, float mult)
{
    if(mult == columns[row]->mult) return;
    columns[row]->mult = mult;
    if(ordinates.contains(row)){
        dataFromFile->fill(ordinates.value(row), abscissRow, row, mult);
        ordinates.value(row)->setTitle(columns[row]->getHeader());
        canvas->replot();
    }
}

float Columns::getMult(int row) const
{
    return columns[row]->mult;
}

void Columns::setHeader(int row, QString header)
{
    columns[row]->header = header;
    if(ordinates.contains(row)){
        ordinates.value(row)->setTitle(header);
        canvas->replot();
    }
}

QString Columns::getHeader(int row) const
{
    return columns[row]->header;
}

QString Columns::getStyle(int row) const
{
    return columns[row]->style;
}

void Columns::setStyle(int row, QString style)
{
    columns[row]->style = style;
    if(ordinates.contains(row)){
        ordinates.value(row)->setStyle(style);
        canvas->replot();
    }
}

bool Columns::isAbsciss(int row) const
{
    return abscissRow == row;
}

bool Columns::isOrdinate(int row) const{
    return ordinates.contains(row);
}

void Columns::setAbscissRow(int row)
{
    if(abscissRow == row) return;
    abscissRow = row;
    foreach(int key, ordinates.keys()){
        dataFromFile->fill(ordinates.value(key), abscissRow, key, columns[key]->mult);
    }
    canvas->replot();
}

void Columns::setOrdinateRow(int row)
{
    if(ordinates.contains(row))
        delete ordinates.take(row);
    else
        addNewPlotCurve(row);
    canvas->ifIsAutoscale();
}

void Columns::replace(DataFromFile* dataFromFile)
{
    this->dataFromFile = dataFromFile;
    this->dataFromFile->replaceDynamicColumns(columns);
    if(abscissRow >= columns.size()) abscissRow = 0;
    foreach(int key, ordinates.keys()){
        delete ordinates.take(key);
        if(key < columns.size()) setOrdinateRow(key);
    }
    canvas->replot();
}

//Write to xml
#include <QXmlStreamWriter>
#include "../Data/FilePathParsing/FilePathParsing.h"
void Columns::save(QXmlStreamWriter &out, QString projectName) const
{
    out.writeStartElement("file");
        //out.writeAttribute("path", _data_from_file->path_to_file().split("/").last());
        out.writeAttribute("path", FilePathParsing::getRelativePath(projectName, dataFromFile->getPathToFile()));
        foreach(DynamicColumn* column, columns) column->save(out);
        out.writeStartElement("index");
            out.writeAttribute("type", "absciss");
            out.writeAttribute("value", QString("%1").arg(abscissRow));
        out.writeEndElement();
        foreach(int key, ordinates.keys()){
            out.writeStartElement("index");
                out.writeAttribute("type", "ordinate");
                out.writeAttribute("value", QString("%1").arg(key));
            out.writeEndElement();
        }
    out.writeEndElement();
}

//Read from xml - data_was_loaded
#include "../Properties/DataFromProject.h"
void Columns::read(const DataFromProject& dataFromProject)
{
    setDynamicColumn(dataFromProject.columns);
    setAbscissRow(dataFromProject.absciss);
    setOrdinateIndexes(dataFromProject.ordinates);
    canvas->replot();
}

void Columns::setDynamicColumn(const QVector<DynamicColumn>& columns)
{
    int n = qMin(columns.size(), columns.size());
    for(int i=0; i<n; ++i){
        this->columns[i]->header = columns[i].header;
        this->columns[i]->mult   = columns[i].mult;
        this->columns[i]->style  = columns[i].style;
    }
}

void Columns::setOrdinateIndexes(const QVector<int>& ordinates)
{
    foreach(int row, ordinates){
        if(row < columns.size() && row >= 0) addNewPlotCurve(row);
    }
}

//Create new plot curve.
void Columns::addNewPlotCurve(int row)
{
    PlotCurve* curve = dataFromFile->getCurve(abscissRow, row, columns[row]);
    ordinates.insert(row, curve);
    curve->attach(canvas);
}
