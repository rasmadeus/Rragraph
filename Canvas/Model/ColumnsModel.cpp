#include "ColumnsModel.h"
#include "Columns.h"

ColumnsModel::ColumnsModel(DataFromFile* dataFromFile, Canvas* canvas, QObject* parent) :
    QAbstractTableModel(parent)
{
    columns = new Columns(dataFromFile, canvas);
}

ColumnsModel::~ColumnsModel()
{
    delete columns;
}

void ColumnsModel::detach()
{
    columns->detach();
}

int ColumnsModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return columns->row();
}

int ColumnsModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 5;
}

Qt::ItemFlags ColumnsModel::flags(const QModelIndex& index) const
{
    if(!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QVariant ColumnsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole || orientation != Qt::Horizontal) return QVariant();
    switch(section){
        case 0  : return tr("Header");
        case 1  : return tr("Absciss");
        case 2  : return tr("Ordinates");
        case 3  : return tr("Mult");
        default : return tr("Style");
    }
}

#include <QColor>
#include <QFont>
QVariant ColumnsModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()) return QVariant();
    if(role == Qt::BackgroundRole && index.row() % 2) return QColor(230, 230, 230);
    if(role == Qt::FontRole){
        QFont font; font.setBold(true); font.setPointSize(font.pointSize() + 1);
        switch(index.column()){
            case 1 : return columns->isAbsciss(index.row())  ? font : QVariant();
            case 2 : return columns->isOrdinate(index.row()) ? font : QVariant();
        }
    }
    if(role == Qt::TextColorRole){
        switch(index.column()){
            case 1 : return columns->isAbsciss(index.row())  ? QColor(130, 0, 0) : QVariant();
            case 2 : return columns->isOrdinate(index.row()) ? QColor(130, 0, 0) : QVariant();
        }
    }
    if(role == Qt::DisplayRole)
        switch(index.column()){
            case 0 : return columns->getHeader(index.row());
            case 1 : return columns->isAbsciss(index.row())  ? tr("Yes") : tr("No");
            case 2 : return columns->isOrdinate(index.row()) ? tr("Yes") : tr("No");
            case 3 : return columns->getMult(index.row());
            case 4 : return columns->getStyle(index.row());
    }
    return QVariant();
}

bool ColumnsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(!index.isValid() || role != Qt::EditRole) return false;
    switch(index.column()){
        case 0 : if(!value.toString().isEmpty())columns->setHeader(index.row(), value.toString()); break;
        case 1 : columns->setAbscissRow(index.row());                                              break;
        case 2 : columns->setOrdinateRow(index.row());                                             break;
        case 3 : columns->setMult(index.row(), value.toFloat());                                   break;
        case 4 : columns->setStyle(index.row(), value.toString());                                 break;
    }
    reset();
    return true;
}

void ColumnsModel::save(QXmlStreamWriter &out, QString projectName) const
{
    columns->save(out, projectName);
}

void ColumnsModel::read(const DataFromProject& dataFromProject)
{
    columns->read(dataFromProject);
}

//Replace data
void ColumnsModel::replace(DataFromFile* dataFromFile)
{
    columns->replace(dataFromFile);
    reset();
}
