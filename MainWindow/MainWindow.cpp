#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../Styles/View/StylesEditor.h"
#include <QProgressBar>
#include "../Canvas/Data/Data.h"
#include "MdiArea/MdiArea.h"
#include "RecentlyClosed/RecentlyClosed.h"

QString MainWindow::projectName;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    styleEditor = new StylesEditor(this);
    recentlyClosed = new RecentlyClosed(ui->menuRecently_closed);
    createArea();
    createSlotsConnections();
    createLanguageMenu();
    createTileBehaviorMenu();
    restoreSettings();
}

void MainWindow::loadProject(const QString &path)
{
    projectName = path;
    readFromProjectName();
}

MainWindow::~MainWindow()
{
    saveSettings();
    if(guide.isRunning()) guide.terminate();
    delete Data::getInstance();
    delete styleEditor;
    delete area;
    delete recentlyClosed;
    delete ui;
}

#include <QMessageBox>
#include <QCloseEvent>
void MainWindow::closeEvent(QCloseEvent* evt)
{
    switch(
        QMessageBox::warning(
            this,
            tr("Exit from Rragraph"),
            tr("Would you like to save the plot customization?"),
            QMessageBox::Yes,
            QMessageBox::No,
            QMessageBox::Cancel
        )
    ){
        case QMessageBox::Yes    : save() ? evt->accept() : evt->ignore(); break;
        case QMessageBox::No     :          evt->accept() ;                break;
        case QMessageBox::Cancel :                          evt->ignore(); break;
    }
}

void MainWindow::resizeEvent(QResizeEvent *evt)
{
    QMainWindow::resizeEvent(evt);
    area->tile();
}

#include <QFileDialog>
void MainWindow::toPdf()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save image to png document..."), reportPdfDir, tr("PDF document (*.pdf)"));
    if(path.isEmpty()) return;
    reportPdfDir = path;
    area->toPdf(path);
}

void MainWindow::toPngImages()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose the dir, where the png image will be saved..."), reportPngDir);
    if(dir.isEmpty()) return;
    reportPngDir = dir;
    area->toPngImages(dir);
}

//About
void MainWindow::about()
{
    QMessageBox::about(
        this,
        tr("About"),
        tr(
            "<font color=\"#840000\"><h3>Rragraph</h3>"
            "OS - Windows XP sp3; Rragraph version  - 3.0;<br>"
            "License - OpenSource Qt and Qwt version 1.0;<br>"
            "Contact  - rasmadeus@gmail.com;</font>"
        )
    );
}

void MainWindow::cleanProject()
{
    area->closeAllSubWindows();
    Data::getInstance()->clear();
    projectName = "";
}

//Interface's options.

//Set button's size as big or as small.
void MainWindow::setBigButton(bool is)
{
    setToolButtonStyle(is ? Qt::ToolButtonTextUnderIcon : Qt::ToolButtonIconOnly);
    QSize size(is ? 44 : 24, 24);
    ui->tb_Project->setIconSize(size);
    ui->tb_Data->   setIconSize(size);
    ui->tb_Windows->setIconSize(size);
    ui->tb_Report-> setIconSize(size);
    ui->tb_Help->   setIconSize(size);
}

//Data's slots

void MainWindow::loadFiles()
{
    Data::getInstance()->loadFiles(this);
}

//Project's slots

//Save project to xml file.
#include <QFileDialog>
bool MainWindow::saveAs()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save this project as..."), getPathToProject(), tr("Rragraph's project (*.rgf)"));
    if(path.isEmpty()) return false;
    projectName = path;
    setWindowTitle(projectName);
    bool result = saveToProjectName();
    recentlyClosed->savePathOfProject(projectName);
    return result;
}

bool MainWindow::save()
{
    return projectName.isEmpty() ? saveAs() : saveToProjectName();
}

#include <QXmlStreamWriter>
void MainWindow::save(QXmlStreamWriter &out)
{
    if(!reportPngDir.isEmpty()){
        out.writeStartElement("path");
            out.writeAttribute("png_report", reportPngDir);
        out.writeEndElement();
    }
    if(!reportPdfDir.isEmpty()){
        out.writeStartElement("path");
            out.writeAttribute("pdf_report", reportPdfDir);
        out.writeEndElement();
    }
    out.writeTextElement("tileType", QString("%1").arg(area->getTileType()));
    area->save(out, projectName);
}

#include <QFile>
#include <QTextCodec>
bool MainWindow::saveToProjectName()
{
    QFile file(projectName);
    if(!file.open(QFile::WriteOnly)) return false;
        QXmlStreamWriter out(&file);
        out.setAutoFormatting(true);
        out.setCodec("cp1251");
        out.writeStartDocument();
            out.writeStartElement("Project");
                save(out);
                Data::getInstance()->save(out, projectName);
            out.writeEndElement();
        out.writeEndDocument();
    file.close();
    return true;
}

//Reading project from xml file.
void MainWindow::readFromProjectName()
{
    QFile file(projectName);
    if(!file.open(QFile::ReadOnly)) return;
    area->closeAllSubWindows();
    Data::getInstance()->clear();
    QXmlStreamReader in(&file);
    while(!in.atEnd()){
        in.readNext();
        read(in);
    }
    file.close();
    recentlyClosed->savePathOfProject(projectName);
    setWindowTitle(projectName);
    area->tile();
}

void MainWindow::read(QXmlStreamReader& in)
{
    if(in.tokenType() == QXmlStreamReader::StartElement){
        if(in.name() == "path"){
            if(in.attributes().size()){
                if(in.attributes().first().name() == "png_report")   reportPngDir = in.attributes().first().value().toString();
                if(in.attributes().first().name() == "pdf_report")   reportPdfDir = in.attributes().first().value().toString();
            }
        }
        if(in.name() == "tileType"){
            setTiler(in.readElementText().toInt());
        }
        if(in.name() == "plot"){
            area->addWindow();
            area->readLast(in);
        }
        if(in.name() == "Data")
            Data::getInstance()->read(in, projectName);
    }
}

#include <QSettings>
QString MainWindow::getPathToProject()
{
    return projectName.isEmpty() ? QSettings().value("Widget settings/MainWindow/LastProjectPath").toString() : projectName;
}

void MainWindow::read()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Read project file..."), getPathToProject(), "*.rgf");
    if(path.isEmpty()) return;
    projectName = path;
    readFromProjectName();
}

void MainWindow::reopen()
{
    projectName.isEmpty() ? read() :readFromProjectName();
}

void MainWindow::setLocale(QString locale)
{
    foreach(QAction* action, languages->actions()){
        if(action->data().toString() == locale){
            action->setChecked(true);
            translator.switchLanguage(action);
            return;
        }
    }
}

//Create MdiArea
void MainWindow::createArea()
{
    area = new MdiArea(ui->mdiArea, this);
    connect(area, SIGNAL(showEditor(QWidget*)), styleEditor, SLOT(showEditor(QWidget*)));
    connect(ui->actionAutoscale, SIGNAL(triggered()),      area, SLOT(autoscale()));
    connect(styleEditor,         SIGNAL(replot()),         area, SLOT(replot()));
    connect(styleEditor,         SIGNAL(setCurvesStyle()), area, SLOT(reloadStyle()));
    connect(ui->actionNewWindow, SIGNAL(triggered()),      area, SLOT(addOneWindow()));
    connect(ui->actionMax,       SIGNAL(triggered()),      area, SLOT(maximizeCurrentWindow()));
    connect(ui->actionTile ,     SIGNAL(triggered()),      area, SLOT(tile()));
    connect(ui->actionCloseSW,   SIGNAL(triggered()),      area, SLOT(closeAllSubWindows()));

    connect(ui->actionToPNG, SIGNAL(triggered()), this, SLOT(toPngImages()));
    connect(ui->actionToPDF, SIGNAL(triggered()), this, SLOT(toPdf()));
}

//Create slots' connections.
void MainWindow::createSlotsConnections()
{
//Options
    connect(ui->actionAbout,        SIGNAL(triggered()),     this,        SLOT(about()));
    connect(ui->actionBigIcons,     SIGNAL(triggered(bool)), this,        SLOT(setBigButton(bool)));
    connect(ui->actionStylesEditor, SIGNAL(triggered()),     styleEditor, SLOT(show()));
//Data
    connect(ui->actionAddData, SIGNAL(triggered()), this, SLOT(loadFiles()));
//Project
    connect(ui->actionSaveAs,      SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionSaveProject, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionOpenProject, SIGNAL(triggered()), this, SLOT(read()));
    connect(ui->actionReopen,      SIGNAL(triggered()), this, SLOT(reopen()));
    connect(ui->actionToClean,     SIGNAL(triggered()), this, SLOT(cleanProject()));
    connect(ui->actionRemovePaths, SIGNAL(triggered()), recentlyClosed, SLOT(removeNonexistentPaths()));
//Guide
    connect(ui->actionGuide, SIGNAL(triggered()),     this, SLOT(callGuide()));
    connect(&guide,          SIGNAL(dataWasShowed()), this, SLOT(dataWasShowed()));
    connect(recentlyClosed,  SIGNAL(readProjectFrom(QString)), this, SLOT(readProjectFrom(QString)));
}

//Saving and restoring the window geometry and state.
void MainWindow::saveSettings() const
{
    QSettings settings;
    settings.beginGroup("Widget settings/MainWindow");
        settings.setValue("Geometry",        saveGeometry());
        settings.setValue("State",           saveState());
        settings.setValue("IsBigIcons",      ui->actionBigIcons->isChecked());
        settings.setValue("Locale",  languages->checkedAction()->data().toString());
        settings.setValue("ReportPngDir", reportPngDir);
        settings.setValue("ReportPdfDir", reportPdfDir);
        if(!projectName.isEmpty()) settings.setValue("LastProjectPath", projectName);
    settings.endGroup();
}

void MainWindow::restoreSettings()
{
    QSettings settings;
    settings.beginGroup("Widget settings/MainWindow");
        restoreGeometry(                 settings.value("Geometry")  .toByteArray());
        restoreState(                    settings.value("State")     .toByteArray());

        ui->actionBigIcons->setChecked(settings.value("IsBigIcons").toBool());
        setBigButton(ui->actionBigIcons->isChecked());

        recentlyClosed->fill(settings);
        reportPngDir = settings.value("ReportPngDir").toString();
        reportPdfDir = settings.value("ReportPdfDir").toString();
        setLocale(settings.value("Locale").toString());
    settings.endGroup();
}

void MainWindow::createLanguageMenu()
{
    languages = new QActionGroup(this);
    translator.createActionGroup(languages);
    ui->menuLanguage->addActions(languages->actions());
    connect(&translator, SIGNAL(retranslate()), this, SLOT(retranslate()));
}

void MainWindow::retranslate()
{
    ui->retranslateUi(this);
    area->retranslate();
    styleEditor->retranslate();
}

void MainWindow::readProjectFrom(QString path)
{
    projectName = path;
    readFromProjectName();
}

void MainWindow::createTileBehaviorMenu()
{
    tilers = new QActionGroup(this);
    ui->actionNormalTile->setData(MdiArea::NORMAL);
    tilers->addAction(ui->actionNormalTile);
    ui->actionHorizontalTile->setData(MdiArea::HORIZONTAL);
    tilers->addAction(ui->actionHorizontalTile);
    connect(tilers, SIGNAL(triggered(QAction*)), area, SLOT(setTileType(QAction*)));
    ui->actionNormalTile->setChecked(true);
    area->setTileType(ui->actionNormalTile);
}


#include <QDesktopServices>
#include <QUrl>
void MainWindow::callGuide()
{
    foreach(QAction* action, ui->menuLanguage->actions()){
        if(action->isChecked()){
            guide.setUrl(action);
            break;
        }
    }
    ui->actionGuide->setEnabled(false);
    guide.start();
}

void MainWindow::dataWasShowed()
{
    ui->actionGuide->setEnabled(true);
}

#include <QDrag>
void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

#include <QUrl>
void MainWindow::dropEvent(QDropEvent* event)
{
    if(event->mimeData()->hasUrls()){
        QStringList data_paths;
        foreach(QUrl url, event->mimeData()->urls()){
            data_paths << url.toLocalFile();
        }
        loadFiles(data_paths);
    }
}

void MainWindow::loadFiles(const QStringList &paths)
{
    foreach(QString path, paths){
        path.contains(".rgf") ? loadProject(path) : Data::getInstance()->pushBack(path);
    }
}

void MainWindow::setTiler(int type)
{
    foreach(QAction* action, ui->menuTileBehavior->actions()){
        if(action->data().toInt() == type){
            action->setChecked(true);
            area->setTileType(action);
            return;
        }
    }
}
