#include "CurveStyleDelegate.h"

CurveStyleDelegate::CurveStyleDelegate(QWidget* parent) :
    QStyledItemDelegate(parent)
{
}

#include <QComboBox>
#include <QStringList>
#include <QSettings>
#include "PainterListItem.h"
QWidget* CurveStyleDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QComboBox* cb = new QComboBox(parent);
    cb->setItemDelegate(new PainterListItem(cb));
    return cb;
}

#include "../../../Styles/Item/Item.h"
#include "../../../Styles/StylesCurve.h"
void CurveStyleDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    QComboBox* cb = static_cast<QComboBox*>(editor);
    StylesCurve::getInstance()->fill(cb);
    cb->setCurrentIndex(cb->findText(index.data().toString()));
}

void CurveStyleDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QComboBox* cb = static_cast<QComboBox*>(editor);
    model->setData(index, cb->currentText());
}

#include <QPainter>
#include "../../../qwt-6.0.1/qwt_symbol.h"
void CurveStyleDelegate::draw(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    QRect rect(option.rect.left() + 2, option.rect.y() + 2, option.rect.width() - 4, option.rect.height() - 4);
    painter->fillRect(rect, Qt::white);

    StyleCurve* style = StylesCurve::getInstance()->value(index.data().toString());

    painter->setPen(style ? style->pen : QPen());
    painter->drawLine(rect.left()+1, rect.center().y(), rect.right(), rect.center().y());

    if(style){
        style->symbol->drawSymbol(painter, rect.center());
    }
}

void CurveStyleDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    draw(painter, option, index);
}
