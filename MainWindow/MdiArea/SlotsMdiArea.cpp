#include "MdiArea.h"

#include "../../Canvas/Canvas.h"
#include "../../Canvas/Data/Data.h"
#include <QMdiSubWindow>
#include <QMdiArea>
void MdiArea::addWindow()
{
    QMdiSubWindow* window = new QMdiSubWindow;
    Canvas* canvas = new Canvas(window);
    window->setWidget(canvas);
    window->setAttribute(Qt::WA_DeleteOnClose);
    area->addSubWindow(window);
    window->setWindowIcon(QIcon(":/resources/MainWindow/window.png"));
    setTitle(window);
    window->show();
    connect(window,           SIGNAL(destroyed()),                    this,   SLOT(windowWasClosed()));
    connect(Data::getInstance(), SIGNAL(dataWasLoaded(DataFromFile*)), canvas, SLOT(dataWasLoaded(DataFromFile*)));
    connect(Data::getInstance(), SIGNAL(dataWasDeleted(int)),          canvas, SLOT(dataWasDeleted(int)));
    connect(canvas, SIGNAL(showStylesEditor(QWidget*)), this, SIGNAL(showEditor(QWidget*)));
}

void MdiArea::autoscale()
{
    foreach(QMdiSubWindow* subWindow, area->subWindowList()){
        static_cast<Canvas*>(subWindow->widget())->autoscale();
    }
}

void MdiArea::replot()
{
    foreach(QMdiSubWindow* subWindow, area->subWindowList()){
        static_cast<Canvas*>(subWindow->widget())->replot();
    }
}

void MdiArea::reloadStyle()
{
    foreach(QMdiSubWindow* subWindow, area->subWindowList()){
        static_cast<Canvas*>(subWindow->widget())->reloadStyle();
    }
}

void MdiArea::maximizeCurrentWindow()
{
    if(area->subWindowList().size()){
        area->currentSubWindow()->showMaximized();
    }
}

void MdiArea::addOneWindow()
{
    addWindow();
    tile();
}

#include <QAction>
#include <QMdiArea>
void MdiArea::setTileType(QAction* action)
{
    tileType = (TileType) action->data().toInt();
    tile();
}

void MdiArea::tile()
{
    scrollToBegin();
    if(tileType == NORMAL){
        stackedTile();
    }
    else{
        horizontalTile();
        scrollToEnd();
    }
}

void MdiArea::closeAllSubWindows()
{
    foreach(QMdiSubWindow* subWindow, area->subWindowList()){
        disconnect(subWindow, SIGNAL(destroyed()), this, SLOT(windowWasClosed()));
    }
    area->closeAllSubWindows();
}

void MdiArea::windowWasClosed()
{
    setTitle();
    tile();
}
