#include "StringDelegate.h"

StringDelegate::StringDelegate(QWidget *parent) :
    QItemDelegate(parent)
{
}

#include <QLineEdit>
QWidget* StringDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return new QLineEdit(parent);
}

void StringDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QLineEdit* delegate = static_cast<QLineEdit*>(editor);
    delegate->setText(index.data().toString());
    delegate->selectAll();
}
