#include "MdiArea.h"

#include <QMdiArea>
#include <QMdiSubWindow>
void MdiArea::setTitle()
{
    foreach(QMdiSubWindow* subWindow, area->subWindowList()){
        setTitle(subWindow);
        subWindow->repaint();
    }
}

void MdiArea::setTitle(QMdiSubWindow *subWindow)
{
    subWindow->setWindowTitle(tr("Plot %1th").arg(1 + area->subWindowList().indexOf(subWindow)));
}

bool MdiArea::isFewWindows()
{
    if (area->subWindowList().count() < 2){
        stackedTile();
        return true;
    }
    return false;
}

#include <QScrollBar>
void MdiArea::scrollToBegin()
{
    area->verticalScrollBar()->setSliderPosition(area->verticalScrollBar()->minimum());
    if(tileType == NORMAL){
        area->horizontalScrollBar()->setSliderPosition(area->horizontalScrollBar()->minimum());
    }
}

void MdiArea::scrollToEnd()
{
    area->verticalScrollBar()->setSliderPosition(area->verticalScrollBar()->maximum());
}
