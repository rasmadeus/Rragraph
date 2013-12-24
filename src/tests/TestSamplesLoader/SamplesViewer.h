#ifndef SAMPLESVIEWER_H
#define SAMPLESVIEWER_H

class Samples;
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
private:
    Ui::SamplesViewer *ui;
    Samples* samples;
};

#endif // SAMPLESVIEWER_H
