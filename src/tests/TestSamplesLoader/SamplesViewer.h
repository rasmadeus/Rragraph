#ifndef SAMPLESVIEWER_H
#define SAMPLESVIEWER_H

class Samples;
class SamplesManager;
class SamplesQListModel;
#include <QDialog>

namespace Ui {
class SamplesViewer;
}

class SamplesViewer : public QDialog
{
    Q_OBJECT

public:
    explicit SamplesViewer(QWidget *parent = 0);
    ~SamplesViewer();
private slots:
    void loadFile();
    void haveBeenLoaded();

    void loadFiles();
    void removeFile();
private:
    Ui::SamplesViewer *ui;
    Samples* samples;

    SamplesManager* manager;
    SamplesQListModel* model;
};

#endif // SAMPLESVIEWER_H
