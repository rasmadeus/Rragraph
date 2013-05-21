#include "PainterListItem.h"

PainterListItem::PainterListItem(QComboBox* parent) :
    QStyledItemDelegate(parent),
    currentIndex(0)
{
}

#include "CurveStyleDelegate.h"
#include <QPainter>
void PainterListItem::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
   QStyledItemDelegate::paint(painter, option, index);
   CurveStyleDelegate::draw(painter, option, index);
}

QSize PainterListItem::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 17);
}

void PainterListItem::setCurrentIndex(int currentIndex)
{
    this->currentIndex = currentIndex;
}
