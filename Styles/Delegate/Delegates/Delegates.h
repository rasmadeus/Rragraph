#ifndef DELEGATES_H
#define DELEGATES_H

class QWidget;
class QAbstractItemModel;
class QModelIndex;
class QPainter;
class QStyleOptionViewItem;

class Delegates
{
private:
    Delegates(const Delegates&);
    Delegates& operator = (const Delegates&);
protected:
    Delegates();
public:
    virtual ~Delegates();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    virtual bool setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
    virtual bool setEditorData(QWidget* editor, const QModelIndex& index) const;
public:
    static Delegates* createIntDelegate(int min, int max);
    static Delegates* createLegendPositionDelegate();
    static Delegates* createMarkerTypeDelegate();
};

#endif // DELEGATES_H
