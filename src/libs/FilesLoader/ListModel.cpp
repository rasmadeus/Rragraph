#include "ListModel.h"

ListModel::ListModel(QObject *parent) :
    QAbstractListModel(parent),
    activeRow(-1)
{
}

Qt::ItemFlags ListModel::flags(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsEnabled;
}

void ListModel::setActiveRow(const QModelIndex& index)
{
    beginResetModel();
        activeRow = index.row();
    endResetModel();
    emit wasActivated(activeRow);
}

bool ListModel::isActiveRow(const QModelIndex& index) const
{
    return index.row() == activeRow;
}

#include <QFont>
QFont ListModel::fontRole(const QModelIndex& index) const
{
    QFont font;
    if(isActiveRow(index)){
        font.setBold(true);
    }
    return font;
}

#include <QColor>
QColor ListModel::backgroundRole(const QModelIndex& index) const
{
    return QColor(isActiveRow(index) ? "#ddd" : "#fff");
}

QVariant ListModel::data(const QModelIndex& index, int role) const
{
    switch(role){
        case Qt::DisplayRole: return displayRole(index);
        case Qt::FontRole: return fontRole(index);
        case Qt::BackgroundRole: return backgroundRole(index);
    }
    return QVariant();
}

void ListModel::resetModel()
{
    beginResetModel();
    endResetModel();
}

int ListModel::getActiveRow() const
{
    return activeRow;
}
