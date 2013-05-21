#include "Canvas.h"
#include "../qwt-6.0.1/qwt_plot_renderer.h"
#include "../qwt-6.0.1/qwt_plot_zoomer.h"
#include "../qwt-6.0.1/qwt_plot_grid.h"
#include "../qwt-6.0.1/qwt_event_pattern.h"
#include "../qwt-6.0.1/qwt_legend.h"
#include "Properties/Properties.h"
#include <QMouseEvent>
#include <QSettings>
#include <QAction>
#include "Data/Data.h"

#include "Curves/PlotCurve.h"
Canvas::Canvas(QWidget* parent) :
    QwtPlot(parent),
    isAutoscale(true)
{
    setupCanvas();
    createZoomer();
    createGrid();
    setPalette(QPalette(Qt::white));
    createProperties();
    defaultInit();
    Data::getInstance()->fill(this);
    canvasSize = properties->canvasSizeInMm();

}

Canvas::~Canvas()
{
    //If project is new then reportPath is empty. It's bad. It will be better,
    //if we will recover any last correct path. We will be able to do it, if we will save this path.
    if(!reportPath.isEmpty()){
        QSettings().setValue("Widget settings/Curves/ReportPath", reportPath);
    }
}

void Canvas::retranslate()
{
    properties->retranslate();
}

QImage Canvas::image(Canvas* canvas, QSize size)
{
    if(size.isEmpty()) size = canvas->getCanvasSizeInMm();
    QwtPlotRenderer pr;
    pr.setLayoutFlag(QwtPlotRenderer::FrameWithScales);
    QImage image(size, QImage::Format_RGB32);
    image.fill(Qt::white);
    pr.renderTo(canvas, image);
    return image;
}

//Write to xml
#include <QXmlStreamWriter>
void Canvas::save(QXmlStreamWriter& out, QString projectName) const
{
    out.writeStartElement("plot");
        if(!currentStyle.isEmpty()) out.writeAttribute("style",         currentStyle);
        if(!reportPath.isEmpty())   out.writeTextElement("report_path", reportPath);
        properties->save(out, projectName);
    out.writeEndElement();
}

//Read from xml
void Canvas::read(QXmlStreamReader& in)
{
    if(in.attributes().size()) setStyle(in.attributes().value("style").toString());
    while(!in.atEnd()){
        in.readNext();
        if(in.name()== "plot") break;
        if(in.tokenType() == QXmlStreamReader::StartElement){
            if(in.name() == "report_path") reportPath = in.readElementText();
            if(in.name() == "Properties")  properties->read(in);
        }
    }
}

void Canvas::dataWasDeleted(int i)
{
    properties->dataWasDeleted(i);
}

void Canvas::autoscale()
{
    setAutoScale(true);
        replot();
    setAutoScale(isAutoscale);
}

void Canvas::ifIsAutoscale()
{
    if(isAutoscale) autoscale();
    replot();
    createAxesIntervalChangedSignal();
}

//Turn on/off the legend.
//legend_position
//0 - left; 1 - right; 2 - bottom; 3 - top; 4 - isn't.
void Canvas::turnLegend(int legendPosition)
{
    legendPosition == 4
    ? insertLegend(NULL)
    : insertLegend(new QwtLegend(this), static_cast<QwtPlot::LegendPosition>(legendPosition));
}

//Set font fot title of the plot.
void Canvas::setTitleFont(const QFont& font)
{
    QwtText title(this->title());
    title.setFont(font);
    setTitle(title);
}

//Set font for the legend if the legend alive and kicking.
void Canvas::setLegendFont(const QFont& font)
{
    if(legend()) legend()->setFont(font);
}

//Set font for the title of the axis.
void Canvas::setAxisTitleFont(Axis axis, const QFont& font)
{
    QwtText title = axisTitle(axis);
    title.setFont(font);
    setAxisTitle(axis, title);
}

//Set next style: all previous slots will be called by this function.
#include "../Styles/Item/Item.h"
void Canvas::setNextStyle()
{
    QSettings settings;
    settings.beginGroup("Styles/" + Item::getCaption(Item::ROOT_PLOT));
        QStringList keys = settings.childGroups();
        int current_index = keys.indexOf(currentStyle);
        current_index = current_index >= keys.size() - 1 ? 0 : current_index + 1;
        if(current_index >=0 && current_index < keys.size())
            setStyle(keys[current_index]);
    settings.endGroup();
}

//Set previous style.
void Canvas::setPreviousStyle()
{
    QSettings settings;
    settings.beginGroup("Styles/" + Item::getCaption(Item::ROOT_PLOT));
        QStringList keys = settings.childGroups();
        int currentIndex = keys.indexOf(currentStyle);
        currentIndex = currentIndex < 1 ? keys.size() - 1 : currentIndex - 1;
        if(currentIndex >=0 && currentIndex < keys.size())
            setStyle(keys[currentIndex]);
    settings.endGroup();
}


QSize Canvas::getCanvasSizeInMm() const
{
    return properties->canvasSizeInMm();
}

//Saving this plot as png image.
#include <QFileDialog>
void Canvas::toPngImage()
{
    QString path = QFileDialog::getSaveFileName(
        properties,
        tr("Specify the PNG image's name..."),
        reportPath.isEmpty() ? QSettings().value("Widget settings/Curves/ReportPath").toString() : reportPath,
        "*.png"
    );
    if(path.isEmpty()) return;
    reportPath = path;
    QImage image = Canvas::image(this);
    image.save(path);
}


//If current event is double click of left button of mouse the plot will be autoscaled.
void Canvas::mouseDoubleClickEvent(QMouseEvent* evt)
{
    if(evt->button() == Qt::LeftButton){
        setAutoScale(true);
        replot();
            zoomer->setZoomBase();
        setAutoScale(isAutoscale);
        createAxesIntervalChangedSignal();
    }
}

//For update axes intreval information.
void Canvas::mouseReleaseEvent(QMouseEvent* evt)
{
    if(evt->button() == Qt::LeftButton || evt->button() == Qt::MidButton)
        createAxesIntervalChangedSignal();
}

//Call properties.
void Canvas::mousePressEvent(QMouseEvent *evt)
{
    if(evt->button() == Qt::RightButton) properties->show();
}

//This methods create the elements of the plot.
void Canvas::setupCanvas()
{
    canvas()->setLineWidth(1);
    canvas()->setFrameStyle(QFrame::Box | QFrame::Plain);
    canvas()->setBorderRadius(10);
    canvas()->setPalette(QPalette(Qt::white));
}

void Canvas::createZoomer()
{
    zoomer = new QwtPlotZoomer(canvas());
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier);
}

void Canvas::createGrid()
{
    QwtPlotGrid* grid = new QwtPlotGrid();
  //  grid->enableXMin(true);
  //  grid->enableYMin(true);
    grid->setMajPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid->setMinPen(QPen(Qt::gray, 0, Qt::DotLine));
    grid->attach(this);
}

void Canvas::createProperties()
{
    properties = new Properties(this);
    connect(properties, SIGNAL(plotTitleChanged(QString)),     this, SLOT(setTitle(QString)));
    connect(properties, SIGNAL(abscissTitleChanged(QString)),  this, SLOT(setAbscissTitle(QString)));
    connect(properties, SIGNAL(ordinateTitleChanged(QString)), this, SLOT(setOrdinateTitle(QString)));
    connect(properties, SIGNAL(abscissMinChanged(double)),     this, SLOT(setAbscissMin(double)));
    connect(properties, SIGNAL(abscissMaxChanged(double)),     this, SLOT(setAbscissMax(double)));
    connect(properties, SIGNAL(abscissStepChanged(double)),    this, SLOT(setAbscissStep(double)));
    connect(properties, SIGNAL(ordinateMinChanged(double)),    this, SLOT(setOrdinateMin(double)));
    connect(properties, SIGNAL(ordinateMaxChanged(double)),    this, SLOT(setOrdinateMax(double)));
    connect(properties, SIGNAL(ordinateStepChanged(double)),   this, SLOT(setOrdinateStep(double)));
    connect(properties, SIGNAL(toPngImage()),                  this, SLOT(toPngImage()));
    connect(properties, SIGNAL(setPreviousStyle()),            this, SLOT(setPreviousStyle()));
    connect(properties, SIGNAL(setNextStyle()),                this, SLOT(setNextStyle()));
    connect(properties, SIGNAL(showStylesEditor(QWidget*)),    this, SIGNAL(showStylesEditor(QWidget*)));
    connect(this, SIGNAL(axesIntervalChanged(double,double,double,double,double,double)), properties, SIGNAL(axesIntervalChanged(double,double,double,double,double,double)));
}

//Other auxiliary methods.
void Canvas::setAutoScale(bool isAutoscale)
{
    setAxisAutoScale(xBottom, isAutoscale);
    setAxisAutoScale(yLeft,   isAutoscale);
}

void Canvas::defaultInit()
{
    QFont defaultFont;
    defaultFont.setWeight(8);
    setAxisFont(xBottom, defaultFont);
    setAxisFont(yLeft, defaultFont);
    setAxisTitleFont(xBottom, defaultFont);
    setAxisTitleFont(yLeft, defaultFont);
}

void Canvas::setIsAutoscale(bool isAutoscale)
{
    this->isAutoscale = isAutoscale;
}

#include <QDebug>
#include "../Styles/Item/Item.h"
#include "../Styles/StyleReader.h"
void Canvas::setStyle(QString key)
{
    currentStyle = key;
    properties->setStyleName(key);
    Item style = StyleReader::plotStyle(key);
        Item* absciss  = style.find(Item::PLOT_ABSCISS_AXIS);
            if(absciss){
                Item* absciss_axis_font = absciss->find(Item::PLOT_ABSCISS_AXIS_FONT);
                Item* absciss_title_font = absciss->find(Item::PLOT_ABSCISS_TITLE_FONT);
                if(absciss_axis_font && absciss_title_font){
                    setAxisFont(xBottom, absciss_axis_font->getValue().value<QFont>());
                    setAxisTitleFont(xBottom, absciss_title_font->getValue().value<QFont>());
                }
            }
        Item* ordinate = style.find(Item::PLOT_ORDINATE_AXIS);
            if(ordinate){
                Item* ordinate_axis_font = ordinate->find(Item::PLOT_ORDINATE_AXIS_FONT);
                Item* ordinate_title_font = ordinate->find(Item::PLOT_ORDINATE_TITLE_FONT);
                if(ordinate_axis_font && ordinate_title_font){
                    setAxisFont(yLeft, ordinate_axis_font->getValue().value<QFont>());
                    setAxisTitleFont(yLeft, ordinate_title_font->getValue().value<QFont>());
                }
            }
        Item* legend   = style.find(Item::PLOT_LEGEND);
            if(legend){
                Item* legend_pos = legend->find(Item::PLOT_LEGEND_POSITION);
                Item* legend_font = legend->find(Item::PLOT_LEGEND_FONT);
                if(legend_pos && legend_font){
                    turnLegend(legend_pos->getValue().toInt());
                    setLegendFont(legend_font->getValue().value<QFont>());
                }
            }
        Item* plot     = style.find(Item::PLOT_STYLE);
            if(plot){
                Item* title = plot->find(Item::PLOT_STYLE_FONT);
                if(title) setTitleFont(title->getValue().value<QFont>());
            }
}


void Canvas::reloadStyle()
{
    setStyle(currentStyle);
}

void Canvas::dataWasLoaded(DataFromFile* dataFromFile)
{
    properties->dataWasLoaded(dataFromFile);
}
