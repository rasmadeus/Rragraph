#ifndef CURVESFILLER_H
#define CURVESFILLER_H

class Curves;
class CurvesFillerModel;
#include <QWidget>

namespace Ui {
class CurvesFiller;
}

class CurvesFiller : public QWidget
{
    Q_OBJECT

public:
    explicit CurvesFiller(QWidget *parent = 0);
    ~CurvesFiller();
    void setCurves(Curves* curves);
public Q_SLOTS:
    void resetModel();
signals:
    void dataWasSetted();
private slots:
    void setModelData(const QModelIndex& index);
private:
    Ui::CurvesFiller *ui;
    CurvesFillerModel* model;
};

#endif // CURVESFILLER_H
