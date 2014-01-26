#ifndef CURVESFILLERMODEL_H
#define CURVESFILLERMODEL_H

class Curves;
#include <QAbstractTableModel>

class CurvesFillerModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CurvesFillerModel(QObject* parent = 0);
    void setCurves(Curves* curves);
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    bool setData(const QModelIndex& index, const QVariant& value = QVariant(), int role = Qt::EditRole);
    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
signals:
    void dataWasSetted();
private:
    bool isActiveX(const QModelIndex& index) const;
    bool isActiveY(const QModelIndex& index) const;
    bool isActiveXorY(const QModelIndex& index) const;
    bool samplesAvailaible() const;
    QString getDisplayRole(const QModelIndex& index) const;
    QString getReducedHeader(int i) const;
    QColor getTextColorRole(const QModelIndex& index) const;
    QFont getFontRole(const QModelIndex& index) const;
    Curves* curves;
};

#endif // CURVESFILLERMODEL_H
