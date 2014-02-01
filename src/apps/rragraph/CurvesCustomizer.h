#ifndef CURVESCUSTOMIZER_H
#define CURVESCUSTOMIZER_H

class SamplesManager;
class CurvesManagerView;
#include <QDialog>

namespace Ui {
class CurvesCustomizer;
}

class CurvesCustomizer : public QDialog
{
    Q_OBJECT
public:
    explicit CurvesCustomizer(SamplesManager* samplesManager, QWidget* parent = 0);
    ~CurvesCustomizer();
    CurvesManagerView* getCurvesManagerView() const;
private:
    Ui::CurvesCustomizer* ui;
    CurvesManagerView* curvesManagerView;
};

#endif // CURVESCUSTOMIZER_H
