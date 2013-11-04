#ifndef HEADERSAMPLES_H
#define HEADERSAMPLES_H

#include "global.h"
#include <QStringList>
#include <QVector>
#include <QObject>

class HeaderSamples : public QObject
{
    Q_OBJECT
    SINGLETON_HEADER(HeaderSamples)
    QVector<QStringList> samples;
public:
    int size(int iFile) const;
    const QString& getHeader(int iFile, int i) const;
    void setHeader(int iFile, int i, const QString& header);
public slots:
    void reset(int iFile);
signals:
    void headerWasChanged(int iFile, int i, const QString& header);
private slots:
    void wasAdded(int iFile);
    void wasRemoved(int iFile);
};

#endif // HEADERSAMPLES_H
