#ifndef CURVESMANAGER_H
#define CURVESMANAGER_H

class Plot;
class Curves;
class Samples;
class SamplesManager;
#include <QObject>
#include <QVector>

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
private slots:
    void newSamplesWasAdded(int i);
    void samplesWasLoaded(int i);
    void samplesIsGoingToRemove(int i);
private:
    void pushBack(const Samples* samples);
    SamplesManager* samplesManager;
    Plot* owner;
    QVector<Curves*> data;
};

#endif // CURVESMANAGER_H
