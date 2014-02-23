#ifndef CURVESMANAGER_H
#define CURVESMANAGER_H

class Plot;
class Curves;
class Samples;
class SamplesManager;
#include <QObject>
#include <QVector>
#include <QJsonArray>

class CurvesManager : public QObject
{
    Q_OBJECT
public:
    CurvesManager(SamplesManager* samplesManager, Plot* owner, QObject* parent = 0);
    ~CurvesManager();
    SamplesManager* getSamplesManager() const;
    Plot* getPlot() const;
    int count() const;
    Curves* getCurves(int i) const;
    void serialize(QJsonObject& plotSettings) const;
    void restore(const QJsonObject& plotSettings);
public slots:
    void resamples();
private slots:
    void newSamplesWasAdded(int i);
    void samplesWasLoaded(int i);
    void samplesIsGoingToRemove(int i);
    void tryRestoreCurves(int i);
private:
    void pushBack(const Samples* samples);
    SamplesManager* samplesManager;
    Plot* owner;
    QVector<Curves*> data;
    QJsonArray curvesSettings;
};

#endif // CURVESMANAGER_H
