#ifndef HEADERDELEGATE_H
#define HEADERDELEGATE_H

#include <QItemDelegate>

class HeaderDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit HeaderDelegate(QWidget* parent = 0);
protected:
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
};

#endif // HEADERDELEGATE_H
