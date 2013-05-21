#include "CurveStyleModel.h"

CurveStyleModel::CurveStyleModel(QObject* parent) :
    Model(Item::ROOT_CURVE, parent)
{
}

void CurveStyleModel::insertNewStyle(int row)
{
    rootItem->insert(row, Item::CURVE_NAME);
    Item* item = rootItem->child(row);
        item->pushBack(Item::CURVE_LINE);
            item->last()->pushBack(Item::CURVE_LINE_DASH, 1);
            item->last()->pushBack(Item::CURVE_LINE_SPACE, 0);
            item->last()->pushBack(Item::CURVE_LINE_WIDTH, 1);
            item->last()->pushBack(Item::CURVE_LINE_COLOR);
        item->pushBack(Item::CURVE_MARKER);
            item->last()->pushBack(Item::CURVE_MARKER_BEGIN_POINT, 0);
            item->last()->pushBack(Item::CURVE_MARKER_STEP, 10);
            item->last()->pushBack(Item::CURVE_MARKER_SIZE, 0);
            item->last()->pushBack(Item::CURVE_MARKER_TYPE, 0);
            item->last()->pushBack(Item::CURVE_MARKER_COLOR);
}
