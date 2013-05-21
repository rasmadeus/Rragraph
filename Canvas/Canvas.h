#ifndef CANVAS_H
#define CANVAS_H

class QWidget;
class QSettings;
class Properties;
class QwtPlotZoomer;
class DataFromFile;
class QXmlStreamWriter;
class QXmlStreamReader;

#include "../qwt-6.0.1/qwt_plot.h"

class Canvas : public QwtPlot{
    Q_OBJECT
public:
    explicit Canvas(QWidget* parent = 0);
    ~Canvas();
    void retranslate();
    static QImage image(Canvas* canvas, QSize size = QSize());
//Write/Read to/from xml
    void save(QXmlStreamWriter& out, QString projectName) const;
    void read(QXmlStreamReader& in);
public slots:
    void dataWasDeleted(int i);
    void autoscale();
    void ifIsAutoscale();
    void setIsAutoscale(bool isAutoscale);
    void turnLegend(int legendPosition); //Turn on/off the legend.
    void setTitleFont(const QFont& font); //Set font fot title of the plot.
    void setLegendFont(const QFont& font); //Set font for the legend if the legend alive and kicking.
    void setAxisTitleFont(Axis axis, const QFont& font); //Set font for the title of the axis.
    void setNextStyle(); //Set next style: all previous slots will be called by this function.
    void setPreviousStyle(); //Set previous style.
    void setStyle(QString key);
    void reloadStyle();
    QSize getCanvasSizeInMm() const;
//Saving this plot as png image.
    void toPngImage();
//The data was loaded.
    void dataWasLoaded(DataFromFile* data_from_file);
signals:
    void showStylesEditor(QWidget*);
protected:
    void mouseDoubleClickEvent(QMouseEvent* evt); //If current event is double click of left button of mouse the plot will be autoscaled.
    void mouseReleaseEvent(QMouseEvent* evt); //For update axes intervals information.
    void mousePressEvent(QMouseEvent* evt); //Call properties.
private:
//This methods create the elements of the plot.
    void setupCanvas();
    void createZoomer();
    void createGrid();
    void createProperties();
//Other auxiliary methods.
    void setAutoScale(bool is_auto_scale);
    void defaultInit();
private:
    QString currentStyle; //The number of current plot style.
    Properties* properties; //The modal dialog having the properties of this plot.
    QwtPlotZoomer* zoomer;
    QString reportPath; //Here we is saving the last report path.
    QSize canvasSize;
    bool isAutoscale;
};

#endif // CANVAS_H
