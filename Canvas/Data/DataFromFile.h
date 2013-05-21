#ifndef DATAFROMFILE_H
#define DATAFROMFILE_H

class Columns;
class PlotCurve;
class DynamicColumn;

#include "Column.h"
#include "ReaderFile.h"

#include <QObject>

class DataFromFile : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DataFromFile)
public:
    explicit DataFromFile(QObject* parent = 0);
    void loadData(QString path); //Filling the _data_from_file.
    void createHeaders(QString firstRow); //Reading first row from file.
    void pushBackValues(QString row); //Parsing row into float values.
    QString getPathToFile() const; //For example: /home/user/data.txt
    QString getFileName() const; //For example: data.txt
    void stopLoadData();//Terminate _reader_file.
    void createDynamicColumns(Columns* columns);
    void replaceDynamicColumns(QVector<DynamicColumn*>& _columns);
    PlotCurve* getCurve(int iX, int iY, const DynamicColumn* col) const;
    void fill(PlotCurve* curve, int iX, int iY, float mult) const;
private slots:
    void destroy();
signals:
    void dataWasLoaded(DataFromFile* dataFromFile);
private:
    QString pathToFile;           //The file has been loaded from this path.
    QVector<Column> dataFromFile;
    ReaderFile readerFile;
};

#endif // DATAFROMFILE_H
