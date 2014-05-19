#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>

class ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListModel(QObject *parent = 0);
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant data(const QModelIndex& index, int role) const;
    int getActiveRow() const;
protected:
    virtual QString displayRole(const QModelIndex& index) const = 0;
    virtual QFont fontRole(const QModelIndex& index) const;
    virtual QColor backgroundRole(const QModelIndex& index) const;
    virtual QColor textColorRole(const QModelIndex& index) const;
public slots:
    void setActiveRow(const QModelIndex& index);
    void resetModel();
signals:
    void wasActivated(int row);
protected:
    bool isActiveRow(const QModelIndex& index) const;
    int activeRow;

};

#endif // LISTMODEL_H
