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
    explicit SamplesProxyView(QWidget* parent = 0);
    ~SamplesProxyView();
    void setSamplesManager(SamplesManager* samplesManager);
    void retranslate();
private slots:
    void setSamples(int i);
    void disabledResetGroup();
    void enabledResetGroup();
    void checkEnabledResetGroup(int i);
    void updateEnabledResetGroup(int i);
    void resetProxyView();
    void setSamplesPathToWindowTitle(int i);
    void restoreWindowTitle();
private:
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
