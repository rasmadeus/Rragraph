#ifndef CURVESMODEL_H
#define CURVESMODEL_H

class Curve;
class Curves;
#include <QAbstractTableModel>

class CurvesModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CurvesModel(QObject* parent = 0);
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    void setCurves(Curves* curves);
    Curves* getCurves() const;
private slots:
    void wasLoaded(int iFile);
private:
    Curves* curves;
};

#endif // CURVESMODEL_H
