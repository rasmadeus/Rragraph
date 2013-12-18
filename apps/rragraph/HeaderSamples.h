#ifndef HEADERSAMPLES_H
#define HEADERSAMPLES_H

#include "global.h"
#include <QVector>
#include <QStringList>
#include <QObject>

class HeaderSamples : public QObject
{
    Q_OBJECT
    SINGLETON_HEADER(HeaderSamples, QObject)
public:
    int size(int iFile) const;
    const QString& getHeader(int iFile, int i) const;
    void setHeader(int iFile, int i, const QString& header);
    void serialize(QJsonObject& root) const;
    void restore(int iFile, const QJsonObject& root);
public slots:
    void reset(int iFile);
signals:
    void headerWasChanged(int iFile, int i, const QString& header);
private slots:
    void wasAdded(int iFile);
    void wasRemoved(int iFile);
private:
    QVector<QStringList> samples;
};

#endif // HEADERSAMPLES_H
