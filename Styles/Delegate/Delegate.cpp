#include "Delegate.h"

Delegate::Delegate(QWidget* parent) :
    QStyledItemDelegate(parent)
{
    delegate = 0;
}

#include "Delegates/Delegates.h"
Delegate::~Delegate()
{
    if(delegate) delete delegate;
}

#include "../Item/Item.h"
QWidget* Delegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Item* item = Item::item(index);
    if(item){
        if(delegate){
            delete delegate;
            delegate = 0;
        }
        if(item->getType() == Item::CURVE_LINE_DASH)          delegate = Delegates::createIntDelegate(1, 50);      else
        if(item->getType() == Item::CURVE_LINE_SPACE)         delegate = Delegates::createIntDelegate(0, 50);      else
        if(item->getType() == Item::CURVE_LINE_WIDTH)         delegate = Delegates::createIntDelegate(0, 10);      else
        if(item->getType() == Item::CURVE_MARKER_BEGIN_POINT) delegate = Delegates::createIntDelegate(0, 1000000); else
        if(item->getType() == Item::CURVE_MARKER_STEP)        delegate = Delegates::createIntDelegate(0, 100000);  else
        if(item->getType() == Item::CURVE_MARKER_SIZE)        delegate = Delegates::createIntDelegate(0, 50);      else
        if(item->getType() == Item::PLOT_LEGEND_POSITION)     delegate = Delegates::createLegendPositionDelegate();else
        if(item->getType() == Item::CURVE_MARKER_TYPE )       delegate = Delegates::createMarkerTypeDelegate();
    }
    return delegate  ?  delegate->createEditor(parent, option, index) : QStyledItemDelegate::createEditor(parent, option, index);
}

void Delegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if(delegate){
        if(delegate->setEditorData(editor, index)) return;
    }
    QStyledItemDelegate::setEditorData(editor, index);
}

void Delegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    if(delegate){
        if(delegate->setModelData(editor, model, index)) return;
    }
    QStyledItemDelegate::setModelData(editor, model, index);
}

void Delegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Item* item = Item::item(index);
    if(item){
        if(item->getType() == Item::CURVE_MARKER){
            drawMarker(painter, option, item);
            return;
        }
        if(item->getType() == Item::CURVE_LINE){
            drawLine(painter, option, item);
            return;
        }
        if(item->getType() == Item::CURVE_NAME){
            drawLine(painter, option, item->find(Item::CURVE_LINE));
            drawMarker(painter, option, item->find(Item::CURVE_MARKER));
        }
    }
    QStyledItemDelegate::paint(painter, option, index);
}

#include "../../qwt-6.0.1/qwt_symbol.h"
#include <QPainter>
#include "../StyleReader.h"
void Delegate::drawMarker(QPainter* painter, const QStyleOptionViewItem& option, Item* marker) const
{
    if(!marker) return;

    QwtSymbol* symbol = StyleReader::symbol(marker);
        symbol->drawSymbol(painter, option.rect.center());
    delete symbol;
}

void Delegate::drawLine(QPainter* painter, const QStyleOptionViewItem& option, Item* line) const
{
    if(!line) return;

    painter->setPen(StyleReader::pen(line));
    painter->drawLine(option.rect.left(), option.rect.center().y(), option.rect.right(), option.rect.center().y());
}
