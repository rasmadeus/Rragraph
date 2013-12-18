#ifndef SAMPLES_H
#define SAMPLES_H

class SamplesPrivateData;

#include <QObject>
class Samples : public QObject
{
    Q_OBJECT
public:
    explicit Samples(QObject *parent = 0);
    ~Samples();
    const QStringList& getHeaders() const;
    const QVector<double>& getColumns(int i) const;
    int count() const;
    const QString& getPathToSrc() const;
    void load(const QString& pathToSrc);
    void reload();
Q_SIGNALS:
    void haveBeenLoaded();
    void haveBeenLoaded(Samples*);
private slots:
    void samplesHaveBeenLoaded();
private:
    SamplesPrivateData* d;
};

#endif // SAMPLES_H
