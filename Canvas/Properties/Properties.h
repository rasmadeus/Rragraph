#ifndef PROPERTIES_H
#define PROPERTIES_H

class AxesParameters;
class DataFromFile;
class Canvas;
class QXmlStreamWriter;
class QXmlStreamReader;
class DataFromProject;

#include <QDialog>
#include <QMap>
#include <QVector>
#include "../Model/DynamicColumn.h"


namespace Ui {
class Properties;
}
class Properties : public QDialog
{
    Q_OBJECT    
public:
    explicit Properties(Canvas* parent);
    ~Properties();
    void retranslate();
//Methods of AxesProperties
    QSize canvasSizeInMm() const;
    void setStyleName(QString name);
    void save(QXmlStreamWriter& out, QString projectName) const;
    void read(QXmlStreamReader& in);    
public slots:
    void dataWasLoaded(DataFromFile* dataFromFile);
    void dataWasDeleted(int i);
    void replace(int i, DataFromFile* dataFromFile);
private:
    bool event(QEvent* evt);
    void readDataFromProject(QXmlStreamReader& in);
    void readFileFromProject(QXmlStreamReader& in);
signals:
//Signals of AxesParameters
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
    void setPreviousStyle();
    void setNextStyle();
    void showStylesEditor(QWidget*);
//QwtPlot signal
    void axesIntervalChanged(double xm, double xM, double xs, double ym, double yM, double ys);
private slots:
    void beginItem();
    void setTitle(); //Set the path to file as Dialog title.
    void setTitle(int i);
    void deleteData();
    void replaceData();
    void addData();
    void createSignalShowStylesEditor();
private:
    Ui::Properties* ui;
    AxesParameters* axesParameters;
    void createChoiceWidgets();
    void createConstWidgetsForStack();
    static const QString GROUP; //For saving the window's geomethry.
    Canvas* canvas;

    QMap<QString, DataFromProject> dataFromProject;
};

#endif // PROPERTIES_H
