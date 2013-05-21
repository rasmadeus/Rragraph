#ifndef DELEGATE_H
#define DELEGATE_H

#include <QStyledItemDelegate>
class Delegates;
class Item;

class Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit Delegate(QWidget* parent = 0);
    ~Delegate();
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
private:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void drawMarker(QPainter* painter, const QStyleOptionViewItem& option, Item* marker) const;
    void drawLine(QPainter* painter, const QStyleOptionViewItem& option, Item* line) const;
private:
    mutable Delegates* delegate;
};

#endif // DELEGATE_H
