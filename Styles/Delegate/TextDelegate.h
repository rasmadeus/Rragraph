#ifndef TEXTDELEGATE_H
#define TEXTDELEGATE_H

#include <QStyledItemDelegate>

class TextDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TextDelegate(QWidget* parent = 0);
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
};

#endif // TEXTDELEGATE_H
