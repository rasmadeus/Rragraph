#include "MdiArea.h"

#include <QMdiSubWindow>
#include <qmath.h>
#include <QScrollBar>
#include <QMdiArea>
void MdiArea::horizontalTile()
{
    QList<QMdiSubWindow*> list = area->subWindowList();
    if (isFewWindows()) return;
    int wHeight = area->height() / list.count();
    if(wHeight < 200) wHeight = 200;
    int y = 0;
    foreach (QMdiSubWindow *subWindow, list){
        subWindow->resize(area->width(), wHeight);
        subWindow->move(0, y);
        y += wHeight;
    }
}

#include <QStyle>
void MdiArea::stackedTile()
{
    QList<QMdiSubWindow*> subWindows = area->subWindowList();
    if(subWindows.isEmpty()) return;

    QRect domain = area->rect();
    const int n = subWindows.size();
    const int ncols = qMax(qCeil(qSqrt(qreal(n))), 1);
    const int nrows = qMax((n % ncols) ? (n / ncols + 1) : (n / ncols), 1);
    const int nspecial = (n % ncols) ? (ncols - n % ncols) : 0;
    int dx = domain.width()  / ncols;
    int dy = domain.height() / nrows;

    if(dx < 300) dx = 300;
    if(dy < 200) dy = 200;

    int i = n - 1;
    for (int row = 0; row < nrows; ++row) {
        const int y1 = int(row * (dy + 1));
        for (int col = 0; col < ncols; ++col) {
            if (row == 1 && col < nspecial)
                continue;
            const int x1 = int(col * (dx + 1));
            int x2 = int(x1 + dx);
            int y2 = int(y1 + dy);
            if (row == 0 && col < nspecial) {
                y2 *= 2;
                if (nrows != 2)
                    y2 += 1;
                else
                    y2 = domain.bottom();
            }

            QWidget *widget = subWindows.at(i--);
            widget->showMinimized();
            widget->showNormal();
            QRect newGeometry = QRect(QPoint(x1, y1), QPoint(x2, y2));
            widget->setGeometry(QStyle::visualRect(widget->layoutDirection(), domain, newGeometry));
        }
    }
}
