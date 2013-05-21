#include "Delegates.h"

//Legend delegate.

//Class.
#include <QComboBox>
#include "../../../qwt-6.0.1/qwt_plot.h"
class Legend: public Delegates{
public:
    virtual ~Legend(){}
    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(option)
        Q_UNUSED(index)
        QComboBox* editor = new QComboBox(parent);
        for(int i=0; i<5; ++i){
            editor->addItem(QwtPlot::getNameLegendPosition(i));
        }
        return editor;
    }

    bool setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QComboBox* _editor = static_cast<QComboBox*>(editor);
        model->setData(index, _editor->currentIndex());
        return true;
    }

    bool setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        static_cast<QComboBox*>(editor)->setCurrentIndex(index.data().toInt());
        return true;
    }
};

//Maker function.
Delegates* Delegates::createLegendPositionDelegate()
{
    return new Legend();
}

//Marker delegate.
//Class.
#include "../../../qwt-6.0.1/qwt_symbol.h"
class Marker: public Legend{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(option)
        Q_UNUSED(index)
        QComboBox* editor = new QComboBox(parent);
        for(int i=0; i<15; ++i){
            editor->addItem(QwtSymbol::getNameSymbol(i));
        }
        return editor;
    }
};

//Maker function.
Delegates* Delegates::createMarkerTypeDelegate()
{
    return new Marker();
}
