#ifndef DOUBLEDELEGATE_H
#define DOUBLEDELEGATE_H

#include <QItemDelegate>

class DoubleDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit DoubleDelegate(QWidget* parent = 0);
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
};

#endif // DOUBLEDELEGATE_H
