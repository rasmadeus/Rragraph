#ifndef SAMPLESPROXYVIEW_H
#define SAMPLESPROXYVIEW_H

class SamplesManager;
class SamplesManagerView;
class SamplesProxyModel;
#include <QDialog>

namespace Ui {
class SamplesProxyView;
}

class SamplesProxyView : public QDialog
{
    Q_OBJECT
public:
    explicit SamplesProxyView(SamplesManager* samplesManager, QWidget* parent = 0);
    ~SamplesProxyView();
private slots:
    void setSamples(int i);
    void disabledResetGroup();
    void enabledResetGroup();
    void checkEnabledResetGroup(int i);
    void updateEnabledResetGroup(int i);
    void setSamplesPathToWindowTitle(int i);
    void restoreWindowTitle();
private:
    void setSamplesManager(SamplesManager* samplesManager);
    void reset();
    void createSamplesManagerView();
    void createSamplesProxyModel();
    void routeProxyViewActions();
    void customizeProxyView();
    void setEnabledResetGroup(bool on);
    Ui::SamplesProxyView* ui;
    SamplesManager* samplesManager;
    SamplesManagerView* samplesManagerView;
    SamplesProxyModel* samplesProxyModel;
};

#endif // SAMPLESPROXYVIEW_H
