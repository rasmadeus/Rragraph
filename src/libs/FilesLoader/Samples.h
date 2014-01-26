#ifndef SAMPLES_H
#define SAMPLES_H

class SamplesPrivateData;

#include <QFileInfo>
#include <QObject>
class Samples : public QObject
{
    Q_OBJECT
public:
    explicit Samples(QObject *parent = 0);
    ~Samples();
    const QStringList& getHeaders() const;
    const QVector<double>& getColumn(int i) const;
    int count() const;
    int height() const;
    const QString& getPathToSrc() const;
    QFileInfo getPathSrcFileInfo() const;
    void load(const QString& pathToSrc);
    void reload();
    bool isLoading() const;
    void waitLoading() const;
    QStringList getProxyHeaders() const;
    void setProxyHeader(const QString& header, int i);
    QVector<double> getProxyColumn(int i) const;
    void setProxyColumnAddend(double addend);
    void setProxyColumnMult(double mult);
    void resetProxyHeaders();
Q_SIGNALS:
    void haveBeenLoaded();
    void haveBeenLoaded(Samples*);
private slots:
    void samplesHaveBeenLoaded();
private:
    SamplesPrivateData* d;
};

#endif // SAMPLES_H
