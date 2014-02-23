#ifndef SAMPLESPROXYMODEL_H
#define SAMPLESPROXYMODEL_H

class Samples;
#include <QAbstractTableModel>

class SamplesProxyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SamplesProxyModel(QObject *parent = 0);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    void setSamples(Samples* samples);
public slots:
    void resetHeaders();
    void resetAddend();
    void resetMult();
    void resetModel();
private:
    Samples* samples;
};

#endif // SAMPLESPROXYMODEL_H
