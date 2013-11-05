#ifndef HEADERSMODEL_H
#define HEADERSMODEL_H

class Samples;
class HeaderSamples;
#include <QAbstractListModel>

class HeadersModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit HeadersModel(QObject *parent = 0);
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    Qt::ItemFlags flags(const QModelIndex& index) const;
public slots:
    void wasChoosen(int iFile);
    void reset(int iFile);
private:
    int iFile;
    HeaderSamples* samples;
};

#endif // HEADERSMODEL_H
