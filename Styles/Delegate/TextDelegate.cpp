#include "TextDelegate.h"

TextDelegate::TextDelegate(QWidget* parent) :
    QStyledItemDelegate(parent)
{
}

#include <QLineEdit>
QWidget* TextDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return new QLineEdit(parent);
}

void TextDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QLineEdit* le = static_cast<QLineEdit*>(editor);
    le->setText(index.data().toString());
    le->selectAll();
}

void TextDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QLineEdit* le = static_cast<QLineEdit*>(editor);
    if(le->text().isEmpty()) return;
    model->setData(index, le->text());
}
