#include "Delegates.h"

Delegates::Delegates()
{
}

Delegates::~Delegates()
{
}

QWidget* Delegates::createEditor(QWidget*, const QStyleOptionViewItem&, const QModelIndex&) const
{
    return 0;
}

bool Delegates::setEditorData(QWidget*, const QModelIndex&) const
{
    return false;
}

bool Delegates::setModelData(QWidget*, QAbstractItemModel*, const QModelIndex&) const
{
    return false;
}
