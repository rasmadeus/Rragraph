#ifndef CURVESTYLEDELEGATE_H
#define CURVESTYLEDELEGATE_H

#include <QStyledItemDelegate>

class CurveStyleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CurveStyleDelegate(QWidget* parent = 0);
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setEditorData(QWidget* editor, const QModelIndex& index) const;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    static void draw(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index);
};

#endif // CURVESTYLEDELEGATE_H
