#ifndef MDIAREA_H
#define MDIAREA_H

class Plot;
#include "global.h"
#include <QMdiArea>
#include "Savable.h"

class MdiArea : public QMdiArea, public Savable
{
    Q_OBJECT
    explicit MdiArea(QWidget *parent = 0);
    static MdiArea* instance;
public:
    QJsonObject serialize() const;
    void restore(const QJsonObject& obj);
public slots:
    static void create(QWidget* parent);
    static MdiArea* getInstance();
    Plot *insertPlot();
    void exportToPng();
    void print();
    void autoscale();
private slots:
    void retitle();
};

#endif // MDIAREA_H
