#include "Model.h"

#include "../Item/Item.h"
Model::Model(Item::Type type, QObject* parent) :
    QAbstractTableModel(parent)
{
    rootItem = new Item(type);
    rootItem->restore("Styles/" + Item::getCaption(type));
}

Model::~Model()
{
    delete rootItem;
}

int Model::rowCount(const QModelIndex& parent) const
{
    return item(parent)->childrenCount();
}

int Model::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QModelIndex Model::index(int row, int column, const QModelIndex& parent) const
{
    if (parent.isValid() && parent.column() != 0) return QModelIndex();
    Item* childItem = item(parent)->child(row);
    return childItem ? createIndex(row, column, childItem) : QModelIndex();
}

QModelIndex Model::parent(const QModelIndex& child) const
{
    if (!child.isValid()) return QModelIndex();
    Item* parentItem = item(child)->getParent();
    return parentItem == rootItem ? QModelIndex() : createIndex(parentItem->getChildNumber(), 0, parentItem);
}

Item* Model::item(const QModelIndex& index) const
{
    if (index.isValid()){
        Item* item = Item::item(index);
        if (item) return item;
    }
    return rootItem;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    return orientation == Qt::Horizontal && role == Qt::DisplayRole ?
           section ? tr("Value") : tr("Key")                        :
           QVariant();
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()) return QVariant();
    Item* item = this->item(index);
    switch(role){
        case Qt::DisplayRole    : return displayRole   (index, item);
        case Qt::FontRole       : return fontRole      (index, item);
        case Qt::BackgroundRole : return backgroundRole(index, item);
        case Qt::DecorationRole : return decorationRole(index, item);
        default                 : return QVariant();
    }
}

bool Model::removeRows(int row, int count, const QModelIndex& parent)
{
    if(row == -1 || item(parent) != rootItem || rootItem->isEmpty()) return false;
    beginRemoveRows(parent, row, row + count - 1);
        for(int i = row; i <= row + count - 1; ++i) rootItem->remove(i);
    endRemoveRows();
    emit dataChanged();
    return true;
}

bool Model::insertRows(int row, int count, const QModelIndex& parent)
{
    Item* item = this->item(parent);
    if(item->getParent()) return false;
    beginInsertRows(parent, row, row + count - 1);
        for(int i = row; i <= row + count - 1; ++i) insertNewStyle(i);
    endInsertRows();
    emit dataChanged();
    return true;
}

Qt::ItemFlags Model::flags(const QModelIndex& index) const
{
    return item(index)->isEditable(index) ? Qt::ItemIsEditable | Qt::ItemIsEnabled : Qt::ItemIsEnabled;
}

bool Model::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(role != Qt::EditRole) return false;
    Item* item = this->item(index);
    item->setValue(value);
    emit dataChanged();
    return true;
}

#include <QFont>
#include "../../qwt-6.0.1/qwt_plot.h"
#include "../../qwt-6.0.1/qwt_symbol.h"
QVariant Model::displayRole(const QModelIndex& index, Item* item) const
{
    if(!index.column()) return item->getCaption();
    if(item->isStyleFont()){
        QFont font = item->getValue().value<QFont>();
        return font.family() + QString(" [%1 pt]").arg(font.pointSize());
    }
    if(item->getType() == Item::PLOT_LEGEND_POSITION) return QwtPlot::getNameLegendPosition(item->getValue().toInt());
    if(item->getType() == Item::CURVE_MARKER_TYPE) return QwtSymbol::getNameSymbol(item->getValue().toInt());
    if(item->isEditable(index)) return item->getValue();
    return QVariant();
}

QVariant Model::fontRole(const QModelIndex& index, Item* item) const
{
    QFont font;
    font.setBold(true);
    if(item->isStyleName() || item->getParent()->isStyleName()) return font;
    if(index.column() && item->isStyleFont()){
        QFont font; int size = font.pointSize();
        font = item->getValue().value<QFont>(); font.setPointSize(size);
        return font;
    }
    return QVariant();
}

#include <QColor>
QVariant Model::backgroundRole(const QModelIndex& index, Item* item) const
{
    if(!item->isStyleColor() || !index.column()) return QVariant();
    return item->getValue().value<QColor>();
}

#include <QIcon>
QVariant Model::decorationRole(const QModelIndex& index, Item* item) const
{
    if(index.column()){
        if(item->getType() == Item::PLOT_LEGEND_POSITION) return QwtPlot::getIconLegendPosition(item->getValue().toInt());
        if(item->getType() == Item::CURVE_MARKER_TYPE)    return QwtSymbol::getIconSymbol(item->getValue().toInt());
        return QVariant();
    }
    if(item->isStyleName())           return QIcon(":/resources/Styles/root_item.png");
    if(item->getParent()->isStyleName()) return QIcon(":/resources/Styles/child_item.png");
    return QVariant();
}

#include "Children/CurveStyleModel.h"
#include "Children/PlotStyleModel.h"
Model* Model::make(Type type)
{
    if(type == PLOT_STYLE_MODEL) return new PlotStyleModel;
    return new CurveStyleModel;
}

void Model::save()
{
    rootItem->save("Styles");
}

void Model::read(QXmlStreamReader& in)
{
    rootItem->read(in);
    reset();
}

void Model::save(QXmlStreamWriter& out)
{
    rootItem->save(out);
}
