#ifndef COLUMNSMODEL_H
#define COLUMNSMODEL_H

class Columns;
class DataFromFile;
class Canvas;
class QXmlStreamWriter;
class DynamicColumn;
class DataFromProject;

#include <QAbstractTableModel>

class ColumnsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ColumnsModel(DataFromFile* dataFromFile, Canvas* canvas, QObject* parent = 0);
    ~ColumnsModel();
    void detach();
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
//Write to xml
    void save(QXmlStreamWriter& out, QString projectName) const;
//Read from xml
    void read(const DataFromProject& dataFromProject);
//Replace data
    void replace(DataFromFile* dataFromFile);
private:
    Columns* columns;
};

#endif // COLUMNSMODEL_H
