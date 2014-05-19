#include "Group.h"

class Iterator
{
public:
    enum Type
    {
        STRAIGHT,
        REVERSE
    };

    static Iterator* make(Type type, const QList<QMdiSubWindow *>& windows);

    Iterator(const QList<QMdiSubWindow*>& windows):
        windows(windows)
    {
    }

    virtual ~Iterator()
    {
    }
    virtual QMdiSubWindow* next() = 0;
protected:
    int i;
    QList<QMdiSubWindow*> windows;
};

class StraightIterator: public Iterator
{
public:
    StraightIterator(const QList<QMdiSubWindow*>& windows):
        Iterator(windows)
    {
        i = windows.size() - 1;
    }
protected:
    QMdiSubWindow* next()
    {
        return windows[i--];
    }
};

class ReverseIterator: public Iterator
{
public:
    ReverseIterator(const QList<QMdiSubWindow*>& windows):
        Iterator(windows)
    {
        i = 0;
    }
protected:
    QMdiSubWindow* next()
    {
        return windows[i++];
    }
};

Iterator* Iterator::make(Type type, const QList<QMdiSubWindow*>& windows)
{
    switch(type){
        case STRAIGHT: return new StraightIterator(windows);
        case REVERSE:  return new ReverseIterator(windows);
        default:       return new StraightIterator(windows);
    }
}

#include <QScrollBar>
class Rearranger
{
public:
    Rearranger(Group* plots, Iterator::Type ITERATOR_TYPE):
        mdiArea(plots)
    {
        windows = plots->visibleWindows();
        iterator = Iterator::make(ITERATOR_TYPE, windows);
    }

    virtual ~Rearranger()
    {
        delete iterator;
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

    Group* mdiArea;
    QList<QMdiSubWindow*> windows;
    Iterator* iterator;
};



#include <QMdiSubWindow>
class Vertical: public Rearranger
{
public:
    Vertical(Group* plots, Iterator::Type ITERATOR_TYPE):
        Rearranger(plots, ITERATOR_TYPE)
    {
    }    

    void rearrange()
    {
        moveScrollBarsToMin();
        QPoint position(0, 0);
        for(int i = 0; i < windows.size() ; ++i){
            QMdiSubWindow* window = iterator->next();
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

};

class VerticalStraight: public Vertical
{
public:
    VerticalStraight(Group* plots):
        Vertical(plots, Iterator::STRAIGHT)
    {
    }
};

class VerticalReverse: public Vertical
{
public:
    VerticalReverse(Group* plots):
        Vertical(plots, Iterator::REVERSE)
    {
    }
    void rearrange()
    {
        Vertical::rearrange();
        moveScrollBarsToMax();
    }
};

#include <QtMath>
class GridRearranger: public Rearranger
{
public:
    GridRearranger(Group* plots, Iterator::Type ITERATOR_TYPE):
        Rearranger(plots, ITERATOR_TYPE)
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

        int x = 0;
        int y = nSpecialWindows ? heightBase : 0;

        for(int s = 0; s < nSpecialWindows; ++s){
            tileGeometry(x, widthSpecial, heightBase, s == (nSpecialWindows - 1));
        }
        for(int r = 0; r < nRows; ++r){
            x = 0;
            for(int c = 0; c < nCols; ++c){
                tileGeometry(x, widthBase, heightBase, c == (nCols - 1), y);
            }
            y += heightBase;
        }
    }
private:
    void tileGeometry(int& x, const int& width, const int& height, bool isLast, int y = 0)
    {
        QMdiSubWindow* window = iterator->next();
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

class GridStraight: public GridRearranger
{
public:
    GridStraight(Group* plots):
        GridRearranger(plots, Iterator::STRAIGHT)
    {
    }
};

class GridReverse: public GridRearranger
{
public:
    GridReverse(Group* plots):
        GridRearranger(plots, Iterator::REVERSE)
    {
    }
    void rearrange()
    {
        GridRearranger::rearrange();
        moveScrollBarsToMax();
    }
};

void Group::tile()
{
    switch(tileType){
        case GRID_STRAIGHT     : GridStraight(this).rearrange();     break;
        case GRID_REVERSE      : GridReverse(this).rearrange();      break;
        case VERTICAL_STRAIGHT : VerticalStraight(this).rearrange(); break;
        case VERTICAL_REVERSE  : VerticalReverse(this).rearrange();  break;
        default                : GridStraight(this).rearrange();     break;
    }
}

