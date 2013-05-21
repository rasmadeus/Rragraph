#ifndef AXESPARAMETERS_H
#define AXESPARAMETERS_H

#include <QWidget>
#include <QList>

class QXmlStreamWriter;
class QXmlStreamReader;
class QLineEdit;
class QDoubleSpinBox;


namespace Ui {
class AxesParameters;
}

class AxesParameters : public QWidget
{
    Q_OBJECT    
public:
    explicit AxesParameters(QWidget* parent = 0);
    ~AxesParameters();
    void retranslate();
    QSize canvasSizeInMm() const;
    void setStyleName(QString name);
//Write/Read to/from xml
    void save(QXmlStreamWriter& out) const;
    void read(QXmlStreamReader& in);
    bool eventFilter(QObject*, QEvent*);
private:
    void readAxis(QXmlStreamReader& in, QLineEdit* caption, QDoubleSpinBox* m, QDoubleSpinBox* M, QDoubleSpinBox* s);
signals:
    void plotTitleChanged(QString);
    void abscissTitleChanged(QString);
    void ordinateTitleChanged(QString);
    void abscissMinChanged(double);
    void abscissMaxChanged(double);
    void abscissStepChanged(double);
    void ordinateMinChanged(double);
    void ordinateMaxChanged(double);
    void ordinateStepChanged(double);
    void toPngImage();
    void previousStyle();
    void nextStyle();
    void setStyle(QString);
    void isAutoscale(bool);
public slots:
//xm - A absciss minimum. xM - A absciss maximum. xs - A absciss axis step.
    void setAxesInterval(double xm, double xM, double xs, double ym, double yM, double ys);
private:
    Ui::AxesParameters* ui;
    static QList<AxesParameters*> objects;
    QString styleName;
};

#endif // AXESPARAMETERS_H
