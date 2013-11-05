#include "HeadersView.h"
#include "ui_HeadersView.h"

#include "HeaderSamples.h"
#include "HeadersModel.h"
#include "StringDelegate.h"
#include "FilesModel.h"
#include "Files.h"
#include "Translator.h"
HeadersView::HeadersView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeadersView)
{
    ui->setupUi(this);

    FilesModel::make(ui->filesChooser);
    filesModel = FilesModel::getInstance();
    headersModel = new HeadersModel(ui->view);

    ui->filesChooser->setModel(filesModel);
    ui->view->setModel(headersModel);
    ui->view->setItemDelegateForColumn(0, new StringDelegate(ui->view));

    connect(Files::getInstance(), SIGNAL(wasAdded(int)), SLOT(wasAdded(int)));
    connect(Files::getInstance(), SIGNAL(wasRemoved(int)), SLOT(wasRemoved(int)));
    connect(ui->view, SIGNAL(clicked(QModelIndex)), ui->view, SLOT(edit(QModelIndex)));
    connect(ui->filesChooser, SIGNAL(currentIndexChanged(int)), headersModel, SLOT(wasChoosen(int)));
    connect(ui->reset, SIGNAL(clicked()), SLOT(resetClicked()));
    connect(Translator::getInstance(), SIGNAL(localeWasChanged()), SLOT(localeWasChanged()));
}

HeadersView::~HeadersView(){    
    delete ui;
}

void HeadersView::localeWasChanged(){
    ui->retranslateUi(this);
}

void HeadersView::wasAdded(int iFile)
{
    Q_UNUSED(iFile)
    if(ui->filesChooser->currentIndex() == -1){
        ui->filesChooser->setCurrentIndex(0);
    }    
}
#include <QDebug>
void HeadersView::wasRemoved(int iFile)
{
    if(iFile){
        ui->filesChooser->setCurrentIndex(iFile - 1);
    }
    else{
        if(ui->filesChooser->count()){
            ui->filesChooser->setCurrentIndex(0);
        }
    }
}

void HeadersView::resetClicked()
{
    int iFile = ui->filesChooser->currentIndex();
    if(iFile < 0){
        return;
    }
    headersModel->reset(iFile);
}
