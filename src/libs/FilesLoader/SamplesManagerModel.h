#ifndef SAMPLESMANAGERMODEL_H
#define SAMPLESMANAGERMODEL_H

class Samples;
class SamplesManager;
#include "ListModel.h"

class SamplesManagerModel : public ListModel
{
    Q_OBJECT
public:
    explicit SamplesManagerModel(QObject *parent = 0);
    void setSamplesManager(SamplesManager* samplesManager);
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    void append(const QString& pathToSrc);
    void remove();
    void replace(const QString& pathToSrc);
protected:
    QString displayRole(const QModelIndex& index) const;
signals:
    void wasCleaned();
private:
    SamplesManager* samplesManager;
};

#endif // SAMPLESMANAGERMODEL_H
