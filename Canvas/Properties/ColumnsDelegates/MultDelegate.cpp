#include "MultDelegate.h"

MultDelegate::MultDelegate(QWidget* parent) :
    QItemDelegate(parent)
{
}

#include <QDoubleSpinBox>
QWidget* MultDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QDoubleSpinBox* sb = new QDoubleSpinBox(parent);
    sb->setDecimals(8);
    sb->setMinimum(-100000);
    sb->setMaximum( 100000);
    return sb;
}

void MultDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QDoubleSpinBox* dsb = static_cast<QDoubleSpinBox*>(editor);
    dsb->setValue(index.data().toDouble());
    dsb->selectAll();
}
