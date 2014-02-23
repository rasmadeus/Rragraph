#ifndef SAMPLES_H
#define SAMPLES_H

class Path;
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
    const QString& getProxyHeader(int i) const;
    void setProxyHeader(const QString& header, int i);
    QVector<double> getProxyColumn(int i) const;
    void setProxyColumnAddend(double addend, int i);
    void setProxyColumnMult(double mult, int i);
    double getProxyColumnAddend(int i) const;
    double getProxyColumnMult(int i) const;
    void resetProxyHeaders();
    void resetProxyAddend();
    void resetProxyMult();
    void serialize(QJsonArray& samplesSettings, const Path& proPath) const;
    void restore(const QJsonObject& sampleSettings);
Q_SIGNALS:
    void haveBeenLoaded();
    void haveBeenLoaded(Samples*);
    void proxyDataWasChanged();
private slots:
    void samplesHaveBeenLoaded();
    void tryRestoreProxySettings();
private:
    SamplesPrivateData* d;
};

#endif // SAMPLES_H
