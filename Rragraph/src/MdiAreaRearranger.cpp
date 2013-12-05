#include "MdiArea.h"

#include <QScrollBar>
class Rearranger
{
public:
    Rearranger(MdiArea* mdiArea):
        mdiArea(mdiArea)
    {
        windows = mdiArea->visibleWindows();
    }
    virtual void rearrange() = 0;
protected:
    void moveScrollBarToMin(QScrollBar* scrollBar)
    {
        const int min = scrollBar->minimum();
        scrollBar->setSliderPosition(min);
    }

    void moveScrollBarToMax(QScrollBar* scrollBar)
    {
        const int max = scrollBar->maximum();
        scrollBar->setSliderPosition(max);
    }

    void moveScrollBarsToMin()
    {
        moveScrollBarToMin(mdiArea->verticalScrollBar());
        moveScrollBarToMin(mdiArea->horizontalScrollBar());
    }
    void moveScrollBarsToMax()
    {
        moveScrollBarToMax(mdiArea->verticalScrollBar());
        moveScrollBarToMax(mdiArea->horizontalScrollBar());
    }

    double width() const{
        return mdiArea->viewport()->geometry().width();
    }

    double height() const{
        return mdiArea->viewport()->geometry().height();
    }

    MdiArea* mdiArea;
    QList<QMdiSubWindow*> windows;
};

#include <QMdiSubWindow>
class Vertical: public Rearranger
{
public:
    Vertical(MdiArea* mdiArea):
        Rearranger(mdiArea)
    {
    }

    void rearrange()
    {
        moveScrollBarsToMin();
        QPoint position(0, 0);
        for(int i = 0; i < windows.size() ; ++i){
            QMdiSubWindow* window = next();
            QRect rect(
                0,
                0,
                width(),
                height() / windows.count()
            );
            window->setGeometry(rect);
            window->move(position);
            position.setY(position.y() + window->height());
        }
    }
protected:
    virtual QMdiSubWindow* next() = 0;
};

class VerticalStraight: public Vertical
{
public:
    VerticalStraight(MdiArea* mdiArea):
        Vertical(mdiArea),
        i(windows.size() - 1)
    {
    }
protected:
    QMdiSubWindow* next(){
        return windows.at(i--);
    }
private:
    int i;
};

class VerticalReverse: public Vertical
{
public:
    VerticalReverse(MdiArea* mdiArea):
        Vertical(mdiArea),
        i(0)
    {
    }
    void rearrange()
    {
        Vertical::rearrange();
        moveScrollBarsToMax();
    }
protected:
    QMdiSubWindow* next(){
        return windows.at(i++);
    }
private:
    int i;
};
#include <QDebug>
#include <QtMath>
class GridHorizontal: public Rearranger
{
public:
    GridHorizontal(MdiArea* mdiArea):
        Rearranger(mdiArea)
    {
    }
    void rearrange()
    {
        if(windows.isEmpty()){
            return;
        }
        moveScrollBarsToMin();


        const int n = windows.size();
        const int nCols = qSqrt(double(n));
        const int nRows = n / nCols;
        const int nSpecialWindows = n - nCols * nRows;
        const int heightBase = qMax(height() / ((nSpecialWindows ? 1 : 0) + nRows), double(150));
        const int widthBase = qMax(width() / nCols, double(250));
        const int widthSpecial = nSpecialWindows ? qMax(width() / nSpecialWindows,double(250)) : 0;

        int i = n - 1;
        int x = 0;
        int y = nSpecialWindows ? heightBase : 0;

        for(int s = 0; s < nSpecialWindows; ++s){
            tileGeometry(i, x, widthSpecial, heightBase, s == nSpecialWindows - 1);
        }
        for(int r = 0; r < nRows; ++r){
            x = 0;
            for(int c = 0; c < nCols; ++c){
                tileGeometry(i, x, widthBase, heightBase, c == nCols - 1, y);
            }
            y += heightBase;
        }
    }
private:
    void tileGeometry(int& i, int& x, const int& width, const int& height, bool isLast, int y = 0)
    {
        QMdiSubWindow* window = windows.at(i--);
        int error = 0;
        if(isLast){
            error = x + width - mdiArea->viewport()->geometry().right();
            if(error > 2){
                error = 0;
            }
        }
        window->setGeometry(0, 0, width - error, height);
        window->move(x, y);
        x += width;
    }
};

void MdiArea::tile()
{
    switch(tileType){
        case GRID_HORIZONTAL   : GridHorizontal(this).rearrange();   break;
        case VERTICAL_STRAIGHT : VerticalStraight(this).rearrange(); break;
        case VERTICAL_REVERSE  : VerticalReverse(this).rearrange();  break;
        default                : GridHorizontal(this).rearrange();   break;
    }
}
