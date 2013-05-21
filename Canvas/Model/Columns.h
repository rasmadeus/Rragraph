#ifndef COLUMNS_H
#define COLUMNS_H

class DataFromFile;
struct DynamicColumn;
class PlotCurve;
class Canvas;
class QXmlStreamWriter;
class DataFromProject;

#include <QVector>
#include <QMap>

class Columns
{
public:
    Columns(DataFromFile* dataFromFile, Canvas* canvas);
    ~Columns();
    void detach();
    void pushBack(QString header); //Push back a new DynamicColumn into _columns.
    int row() const; //The _columns's size.
    void setMult(int row, float mult);
    float getMult(int row) const;
    void setHeader(int row, QString header);
    QString getHeader(int row) const;
    QString getStyle(int row) const;
    void setStyle(int row, QString style);
    bool isAbsciss(int row) const;
    bool isOrdinate(int row) const;
    void setAbscissRow(int row);
    void setOrdinateRow(int row);
    void replace(DataFromFile* dataFromFile);
//Write to xml
    void save(QXmlStreamWriter &out, QString projectName) const;
//Read from xml - data_was_loaded
    void read(const DataFromProject& dataFromProject);
private:
    void addNewPlotCurve(int row);
    void setDynamicColumn(const QVector<DynamicColumn>& columns);
    void setOrdinateIndexes(const QVector<int>& ordinates);
private:
    QVector<DynamicColumn*> columns;
    int abscissRow;
    QMap<int, PlotCurve*> ordinates;
    DataFromFile* dataFromFile;
    Canvas* canvas;
};

#endif // COLUMNS_H
