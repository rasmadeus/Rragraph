#include "PlotStyleModel.h"

PlotStyleModel::PlotStyleModel(QObject *parent) :
    Model(Item::ROOT_PLOT, parent)
{
}

#include <QFont>
void PlotStyleModel::insertNewStyle(int row)
{
    rootItem->insert(row, Item::PLOT_NAME);
    Item* item = rootItem->child(row);
        item->pushBack(Item::PLOT_STYLE);
            item->last()->pushBack(Item::PLOT_STYLE_FONT, QFont());
        item->pushBack(Item::PLOT_LEGEND);
            item->last()->pushBack(Item::PLOT_LEGEND_FONT, QFont());
            item->last()->pushBack(Item::PLOT_LEGEND_POSITION, 0);
        item->pushBack(Item::PLOT_ABSCISS_AXIS);
            item->last()->pushBack(Item::PLOT_ABSCISS_AXIS_FONT, QFont());
            item->last()->pushBack(Item::PLOT_ABSCISS_TITLE_FONT, 0);
        item->pushBack(Item::PLOT_ORDINATE_AXIS);
            item->last()->pushBack(Item::PLOT_ORDINATE_AXIS_FONT, QFont());
            item->last()->pushBack(Item::PLOT_ORDINATE_TITLE_FONT, 0);
}
