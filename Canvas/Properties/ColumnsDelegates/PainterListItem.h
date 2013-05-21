#ifndef PAINTERLISTITEM_H
#define PAINTERLISTITEM_H

#include <QStyledItemDelegate>
#include <QComboBox>

class PainterListItem : public QStyledItemDelegate
{
    Q_OBJECT
private:
    int currentIndex;
private slots:
    void setCurrentIndex(int currentIndex);
public:
    explicit PainterListItem(QComboBox* parent);
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

#endif // PAINTERLISTITEM_H
