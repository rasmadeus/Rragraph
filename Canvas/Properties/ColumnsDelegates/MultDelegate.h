#ifndef MULTDELEGATE_H
#define MULTDELEGATE_H

#include <QItemDelegate>

class MultDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit MultDelegate(QWidget* parent = 0);
protected:
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
};

#endif // MULTDELEGATE_H
