#include "CurveSettingsView.h"
#include "ui_CurveSettingsView.h"

SINGLETON_IMPLEMENTATION(CurveSettingsView, QWidget)

#include "FilesModel.h"
#include "CurvesModel.h"
#include "Files.h"
#include "DoubleDelegate.h"
#include "CurveSettings.h"
#include <QSettings>
CurveSettingsView::CurveSettingsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CurveSettingsView),
    owner(nullptr)
{
    ui->setupUi(this);

    curvesModel = new CurvesModel(this);
    curveSettings = new CurveSettings(this);

    ui->files->setModel(FilesModel::getInstance());
    ui->curveSettings->setModel(curvesModel);
    ui->curveSettings->resizeColumnsToContents();
    ui->curveSettings->setItemDelegateForColumn(3, new DoubleDelegate(ui->curveSettings));

    connect(ui->files,            SIGNAL(clicked(QModelIndex)),   SLOT(setCurves(QModelIndex)));
    connect(ui->files,            SIGNAL(activated(QModelIndex)), SLOT(setCurves(QModelIndex)));
    connect(Files::getInstance(), SIGNAL(wasLoaded(int)),         SLOT(wasLoaded(int)));
    connect(ui->remove,           SIGNAL(clicked()),              SLOT(removeSamples()));
    connect(ui->curveSettings,    SIGNAL(clicked(QModelIndex)),   SLOT(clickedToCurvesView(QModelIndex)));
    connect(ui->insert,           SIGNAL(clicked()),              SLOT(loadFiles()));
    connect(ui->replace,          SIGNAL(clicked()),              SLOT(reloadFile()));
    connect(Files::getInstance(), SIGNAL(wasRemovedAll()),        SLOT(wasRemovedAllFiles()));

    restoreGeometry(QSettings().value("CurveSettingsView/geometry").toByteArray());
}

CurveSettingsView::~CurveSettingsView(){
    QSettings().setValue("CurveSettingsView/geometry", saveGeometry());
    delete ui;
}

void CurveSettingsView::localeWasChanged(){
    ui->retranslateUi(this);
    curveSettings->localeWasChanged();
}

#include "Plot.h"
#include <QFileInfo>
void CurveSettingsView::setCurves(const QModelIndex& index){
    if(index.isValid()){
        setWindowTitle(Files::getInstance()->getPath(index.row()).absoluteFilePath());
    }
    curvesModel->setCurves(owner ? owner->getCurves(index.row()) : nullptr);
}

void CurveSettingsView::wasRemovedAllFiles(){
    setWindowTitle(tr("Curves' creator"));
}

void CurveSettingsView::setOwner(Plot* owner)
{
    this->owner = owner;
    setCurves(ui->files->currentIndex());
}

void CurveSettingsView::show()
{
    if(!ui->files->currentIndex().isValid()){
        const int nFiles = FilesModel::getInstance()->rowCount(QModelIndex());
        if(nFiles){
            const QModelIndex& index = FilesModel::getInstance()->index(0);
            ui->files->setCurrentIndex(index);
            setCurves(index);
        }
    }
    QDialog::show();
}

void CurveSettingsView::loadFiles()
{
    setVisible(false);
    Files::getInstance()->load();
    setVisible(true);
}

void CurveSettingsView::reloadFile()
{
    setVisible(false);
    Files::getInstance()->reload(ui->files->currentIndex().row());
    setVisible(true);
}

void CurveSettingsView::wasLoaded(int iFile)
{
    if(isVisible() && iFile == ui->files->currentIndex().row()){
        setCurves(ui->files->currentIndex());
    }
}

void CurveSettingsView::removeSamples(){
    if(ui->files->currentIndex().isValid()){
        const int currentRow = ui->files->currentIndex().row();
        Files::getInstance()->remove(ui->files->currentIndex().row());
        const int nFiles = FilesModel::getInstance()->rowCount(QModelIndex());
        if(!nFiles){
            curvesModel->setCurves(nullptr);
            ui->curveSettings->reset();
            setWindowTitle(tr("Curves' creator"));
        }
        else{
            const QModelIndex& index = FilesModel::getInstance()->index(currentRow ? currentRow - 1 : 0);
            ui->files->setCurrentIndex(index);
            setCurves(index);
        }
    }
}

void CurveSettingsView::setXYData(const QModelIndex& index)
{
    curvesModel->setData(index, QVariant());
    ui->curveSettings->closePersistentEditor(index);
}

#include <QColorDialog>
void CurveSettingsView::setColorData(const QModelIndex& index)
{
    setVisible(false);
    QColor color = QColorDialog::getColor(
    curvesModel->data(index, Qt::BackgroundRole).value<QColor>(),
        this,
        tr("Set the curve color")
    );
    if(color.isValid()){
        curvesModel->setData(index, color);
    }
    setVisible(true);
}

void CurveSettingsView::setOtherData(const QModelIndex& index)
{
    setVisible(false);
    curveSettings->setModel(curvesModel->getCurves(), index.row());
    curveSettings->exec();
    setVisible(true);
}

void CurveSettingsView::clickedToCurvesView(const QModelIndex& index)
{
    switch(index.column()){
        case 0: setXYData(index);               break;
        case 1: setXYData(index);               break;
        case 2: setColorData(index);            break;
        case 3: ui->curveSettings->edit(index); break;
        case 4: setOtherData(index);            break;
    }
}
