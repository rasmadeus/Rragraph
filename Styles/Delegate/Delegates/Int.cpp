#include "Delegates.h"

//Int delegate.

//Class.
#include <QIntValidator>
#include <QLineEdit>
#include <QModelIndex>
class Int: public Delegates{    
public:

    Int(int min, int max):
        min(min), max(max)
    {
    }

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        Q_UNUSED(option)
        Q_UNUSED(index)
        QLineEdit* editor = new QLineEdit(parent);
        editor->setValidator(new QIntValidator(min, max, editor));
        return editor;
    }

    bool setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QLineEdit* _editor = static_cast<QLineEdit*>(editor);
        _editor->setText(index.data().toString());
        return true;
    }

    bool setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
    {
        QLineEdit* _editor = static_cast<QLineEdit*>(editor);
        if(index.data().toString() == _editor->text()) return true;
        model->setData(index, _editor->text());
        return true;
    }

private:
    int min, max;
};

//Maker function.
Delegates* Delegates::createIntDelegate(int min, int max)
{
    return new Int(min, max);
}
