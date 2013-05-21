#ifndef COLUMNSPROPERTIES_H
#define COLUMNSPROPERTIES_H

class DataFromFile;
class QModelIndex;
class Canvas;
class QXmlStreamWriter;
class DynamicColumn;
class DataFromProject;

#include <QWidget>

namespace Ui {
class ColumnsProperties;
}

class ColumnsProperties : public QWidget
{
    Q_OBJECT
    
public:
    ColumnsProperties(DataFromFile* dataFromFile, Canvas* canvas, QWidget* parent = 0);
    ~ColumnsProperties();
    void detach();
    QString getPathToFile() const;
//Write to xml
    void save(QXmlStreamWriter& out, QString projectName) const;
//Read from xml
    void read(const DataFromProject& dataFromProject);
//Replace data
    void replace(DataFromFile* dataFromFile);
private:
    Ui::ColumnsProperties* ui;
    DataFromFile* dataFromFile;
private slots:
    void clickToTableView(const QModelIndex& index);
};

#endif // COLUMNSPROPERTIES_H
