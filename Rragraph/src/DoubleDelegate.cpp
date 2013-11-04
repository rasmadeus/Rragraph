#include "DoubleDelegate.h"

DoubleDelegate::DoubleDelegate(QWidget *parent) :
    QItemDelegate(parent)
{
}

#include <QDoubleSpinBox>
QWidget* DoubleDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QDoubleSpinBox* delegate = new QDoubleSpinBox(parent);
    delegate->setMinimum(-1000000);
    delegate->setMaximum(1000000);
    delegate->setDecimals(6);
    return delegate;
}

void DoubleDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QDoubleSpinBox* delegate = static_cast<QDoubleSpinBox*>(editor);
    delegate->setValue(index.data().toDouble());
    delegate->selectAll();
}
