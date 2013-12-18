#ifndef SAMPLESLISTMODEL_H
#define SAMPLESLISTMODEL_H

#include <QAbstractListModel>

class SamplesListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SamplesListModel(QObject *parent = 0);
private:

};

#endif // SAMPLESLISTMODEL_H
