#ifndef SAMPLESQLISTMODEL_H
#define SAMPLESQLISTMODEL_H

class SamplesManager;
#include <QAbstractListModel>

class SamplesQListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SamplesQListModel(QObject *parent = 0);
    void setSamplesManager(SamplesManager* samplesManager);
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    bool removeRows(int row, int count, const QModelIndex& parent);
public slots:
    void resetModel();
private:
    SamplesManager* samplesManager;
};

#endif // SAMPLESQLISTMODEL_H
