#ifndef DATAFROMPROJECT_H
#define DATAFROMPROJECT_H

#include "../Model/DynamicColumn.h"
#include <QVector>
#include <QXmlStreamReader>
#include <QObject>

struct DataFromProject{
    QVector<DynamicColumn> columns;
    QVector<int> ordinates;
    int absciss;
    DataFromProject(): absciss(0){}
//Read from xml
    void read(QXmlStreamReader& in){
        if(in.tokenType() == QXmlStreamReader::StartElement){
            if(in.name() == "column"){
                DynamicColumn column;
                column.read(in);
                columns.push_back(column);
            }
            if(in.name() == "index"){
                if(in.attributes().value("type") == "ordinate"){
                    QString value = in.attributes().value("value").toString();
                    if(!value.isEmpty()) ordinates.push_back(value.toInt());
                }
                if(in.attributes().value("type") == "absciss"){
                    QString value = in.attributes().value("value").toString();
                    if(!value.isEmpty()) absciss = value.toInt();
                }
            }
        }
    }
};

#endif // DATAFROMPROJECT_H
