#ifndef SAMPLESMANAGERVIEW_H
#define SAMPLESMANAGERVIEW_H

class SamplesManager;
class SamplesManagerModel;
#include "Path.h"
#include <QWidget>

namespace Ui {
    class SamplesManagerView;
}

class SamplesManagerView : public QWidget
{
    Q_OBJECT
public:
    explicit SamplesManagerView(QWidget *parent = 0);
    ~SamplesManagerView();
    void setSamplesManager(SamplesManager* samplesManager);
    int getActiveRow() const;
    SamplesManager* getSamplesManager() const;
signals:
    void wasActivated(int i);
    void wasCleaned();
private slots:
    void insertNewSamples();
    void removeSamples();
    void replaceSamples();
    void enabledChangableActions();
    void disabledChangableActions();
private:
    void createSamplesManagerModel();
    void routeManagerActions();
    Ui::SamplesManagerView *ui;
    SamplesManagerModel* samplesManagerModel;
    static Path samplesLoadingPath;
};

#endif // SAMPLESMANAGERVIEW_H
