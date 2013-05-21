#include "Properties.h"
#include "ui_Properties.h"
#include <QListWidget>
#include "AxesParameters.h"
#include <QSettings>
#include "../Data/DataFromFile.h"
#include "../Canvas.h"
#include "../../Canvas/Data/Data.h"

const QString Properties::GROUP = "Widget settings/Properties/Geometry";

Properties::Properties(Canvas *parent) :
    QDialog(parent),
    ui(new Ui::Properties),
    canvas(parent)
{
    ui->setupUi(this);
    createConstWidgetsForStack();
    createChoiceWidgets();
    QSettings settings;
    restoreGeometry(settings.value(GROUP).toByteArray());
    connect(Data::getInstance(), SIGNAL(dataWasReplaced(int,DataFromFile*)), this, SLOT(replace(int,DataFromFile*)));
    connect(ui->toolButton, SIGNAL(clicked()), Data::getInstance(), SLOT(cleanFiles()));
}

Properties::~Properties()
{
    QSettings settings;
    settings.setValue(GROUP, saveGeometry());
    delete ui;
}

void Properties::retranslate()
{
    ui->retranslateUi(this);
    axesParameters->retranslate();
}

QSize Properties::canvasSizeInMm() const
{
    return axesParameters->canvasSizeInMm();
}

void Properties::setStyleName(QString name)
{
    axesParameters->setStyleName(name);
}

#include "ColumnsProperties.h"
#include <QXmlStreamReader>
void Properties::save(QXmlStreamWriter &out, QString project_name) const
{
    out.writeStartElement("Properties");
        static_cast<AxesParameters*>   (ui->stackedWidget->widget(0))->save(out);
        out.writeStartElement("ColumnsProperties");
            for(int i=1; i<ui->stackedWidget->count(); ++i)
                static_cast<ColumnsProperties*>(ui->stackedWidget->widget(i))->save(out, project_name);
        out.writeEndElement();
    out.writeEndElement();
}

void Properties::read(QXmlStreamReader &in)
{
    dataFromProject.clear();
    while(!in.atEnd()){
        in.readNext();
        if(in.name() == "Properties") break;
        if(in.tokenType() == QXmlStreamReader::StartElement){
            if(in.name() == "AxesParameters") static_cast<AxesParameters*>(ui->stackedWidget->widget(0))->read(in);
            if(in.name() == "ColumnsProperties") readDataFromProject(in);
        }
    }
}

bool Properties::event(QEvent *evt)
{
    if (evt->type() == QEvent::WindowDeactivate)
        hide();
    return QDialog::event(evt);
}

void Properties::readDataFromProject(QXmlStreamReader &in)
{
    while(!in.atEnd()){
        in.readNext();
        if(in.name() == "ColumnsProperties") break;
        if(in.tokenType() == QXmlStreamReader::StartElement)
            if(in.name() == "file") readFileFromProject(in);
    }
}

#include "DataFromProject.h"
#include <QFileInfo>
void Properties::readFileFromProject(QXmlStreamReader &in)
{
    QString path = in.attributes().value("path").toString();
    DataFromProject data_from_project;
    while(!in.atEnd()){
        in.readNext();
        if(in.name() == "file") break;
        data_from_project.read(in);
    }
    dataFromProject[path] = data_from_project;
}

void Properties::createChoiceWidgets()
{
    ui->listWidget->setIconSize(QSize(24, 24));
    ui->listWidget->addItem(new QListWidgetItem(QIcon(":/resources/Canvas/canvas_properties.png"), tr("Canvas"), ui->listWidget));
    connect(ui->toolButton_3, SIGNAL(clicked()), this, SLOT(beginItem()));
    connect(ui->toolButton_6, SIGNAL(clicked()), this, SLOT(addData()));
    connect(ui->toolButton_4, SIGNAL(clicked()), this, SLOT(deleteData()));
    connect(ui->toolButton_5, SIGNAL(clicked()), this, SLOT(replaceData()));
    connect(ui->toolButton_7, SIGNAL(clicked()), this, SLOT(createSignalShowStylesEditor()));
}

void Properties::createConstWidgetsForStack()
{
    axesParameters = new AxesParameters(ui->stackedWidget);
    ui->stackedWidget->addWidget(axesParameters);

    connect(axesParameters, SIGNAL(plotTitleChanged(QString)),     this, SIGNAL(plotTitleChanged(QString)));
    connect(axesParameters, SIGNAL(abscissTitleChanged(QString)),  this, SIGNAL(abscissTitleChanged(QString)));
    connect(axesParameters, SIGNAL(ordinateTitleChanged(QString)), this, SIGNAL(ordinateTitleChanged(QString)));
    connect(axesParameters, SIGNAL(abscissMinChanged(double)),     this, SIGNAL(abscissMinChanged(double)));
    connect(axesParameters, SIGNAL(abscissMaxChanged(double)),     this, SIGNAL(abscissMaxChanged(double)));
    connect(axesParameters, SIGNAL(abscissStepChanged(double)),    this, SIGNAL(abscissStepChanged(double)));
    connect(axesParameters, SIGNAL(ordinateMinChanged(double)),    this, SIGNAL(ordinateMinChanged(double)));
    connect(axesParameters, SIGNAL(ordinateMaxChanged(double)),    this, SIGNAL(ordinateMaxChanged(double)));
    connect(axesParameters, SIGNAL(ordinateStepChanged(double)),   this, SIGNAL(ordinateStepChanged(double)));
    connect(axesParameters, SIGNAL(toPngImage()),                  this, SIGNAL(toPngImage()));
    connect(axesParameters, SIGNAL(previousStyle()),               this, SIGNAL(setPreviousStyle()));
    connect(axesParameters, SIGNAL(nextStyle()),                   this, SIGNAL(setNextStyle()));

    connect(axesParameters, SIGNAL(setStyle(QString)), canvas, SLOT(setStyle(QString)));
    connect(axesParameters, SIGNAL(isAutoscale(bool)), canvas, SLOT(setIsAutoscale(bool)));

    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), ui->stackedWidget, SLOT(setCurrentIndex(int)));
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(setTitle()));

    connect(
        this,
        SIGNAL(axesIntervalChanged(double,double,double,double,double,double)),
        axesParameters,
        SLOT(  setAxesInterval    (double,double,double,double,double,double))
    );
}

void Properties::beginItem()
{
    ui->listWidget->setCurrentRow(0);
    setTitle();
}

//Set the path to file as Dialog title.
#include "ColumnsProperties.h"
void Properties::setTitle()
{
    if(!ui->listWidget->currentRow()){
        setWindowTitle(tr("Plot properties"));
        return;
    }
    ColumnsProperties* cp = static_cast<ColumnsProperties*>(ui->stackedWidget->currentWidget());
    setWindowTitle(cp->getPathToFile());
}

void Properties::setTitle(int i)
{
    if(!i){
        setWindowTitle(tr("Plot properties"));
        return;
    }
    ColumnsProperties* cp = static_cast<ColumnsProperties*>(ui->stackedWidget->widget(i));
    setWindowTitle(cp->getPathToFile());
}

void Properties::deleteData()
{
    if(!ui->stackedWidget->currentIndex()) return;
    Data::getInstance()->deleteData(ui->stackedWidget->currentIndex()-1);
}

void Properties::replaceData()
{
     if(!ui->stackedWidget->currentIndex()) return;
    Data::getInstance()->replaceData(ui->stackedWidget->currentIndex()-1, this);
}

void Properties::addData()
{
    Data::getInstance()->loadFiles(this);
}

void Properties::createSignalShowStylesEditor()
{
    emit showStylesEditor(this);
}

#include "../Data/FilePathParsing/FilePathParsing.h"
#include "../../MainWindow/MainWindow.h"
void Properties::dataWasLoaded(DataFromFile* dataFromFile)
{
    ColumnsProperties* cp = new ColumnsProperties(dataFromFile, canvas, ui->stackedWidget);
    QString fileName = FilePathParsing::getRelativePath(MainWindow::getPathToProject(),dataFromFile->getPathToFile());
    ui->stackedWidget->addWidget(cp);
    ui->listWidget->addItem(
        new QListWidgetItem(
            QIcon(ui->listWidget->count() % 2 ? ":/resources/Canvas/file_right.png" : ":/resources/Canvas/file_left.png"),
            fileName,
            ui->listWidget
        )
    );
    if(dataFromProject.contains(fileName))
        cp->read(dataFromProject.value(fileName));
}

void Properties::dataWasDeleted(int i)
{
    delete ui->listWidget->takeItem(i + 1);
    QWidget* columnsProperties = ui->stackedWidget->widget(i + 1);
    static_cast<ColumnsProperties*>(columnsProperties)->detach();
    ui->stackedWidget->removeWidget(columnsProperties);
    delete columnsProperties;
}

#include <QFileInfo>
void Properties::replace(int i, DataFromFile *dataFromFile)
{
    QWidget* columnsProperties = ui->stackedWidget->widget(i + 1);
    static_cast<ColumnsProperties*>(columnsProperties)->replace(dataFromFile);
    ui->listWidget->item(i + 1)->setText(QFileInfo(dataFromFile->getPathToFile()).fileName());
    setTitle(i+1);
}
