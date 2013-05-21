#ifndef MODEL_H
#define MODEL_H

#include "../Item/Item.h"
#include <QAbstractTableModel>

class Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Model(Item::Type type, QObject* parent = 0);
    virtual ~Model();
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex& child) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex& index, int role) const;
    bool removeRows(int row, int count, const QModelIndex& parent);
    bool insertRows(int row, int count, const QModelIndex& parent);
    Qt::ItemFlags flags(const QModelIndex& index) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
public:
    enum Type{
        PLOT_STYLE_MODEL,
        CURVE_STYLE_MODEL
    };
    static Model* make(Type type);
public slots:
    void save();
    void read(QXmlStreamReader& in);
    void save(QXmlStreamWriter& out);
protected:
    virtual void insertNewStyle(int row) = 0;
private:
    Item* item(const QModelIndex& index) const;
    QVariant displayRole(const QModelIndex& index, Item* item) const;
    QVariant fontRole(const QModelIndex& index, Item* item) const;
    QVariant backgroundRole(const QModelIndex& index, Item* item) const;
    QVariant decorationRole(const QModelIndex& index, Item* item) const;
protected:
    Item* rootItem;
signals:
    void dataChanged();
};

#endif // MODEL_H
