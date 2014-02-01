#ifndef SAMPLESMANAGERVIEW_H
#define SAMPLESMANAGERVIEW_H

class SamplesManager;
class SamplesManagerModel;
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
signals:
    void wasActivated(int i);
private slots:
    void insertNewSamples();
    void removeSamples();
    void replaceSamples();
private:
    Ui::SamplesManagerView *ui;
    SamplesManagerModel* samplesManagerModel;
};

#endif // SAMPLESMANAGERVIEW_H
