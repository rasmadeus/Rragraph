#include "ColumnsProperties.h"
#include "ui_ColumnsProperties.h"
#include "../Model/ColumnsModel.h"
#include "../Model/Columns.h"
#include "../Data/DataFromFile.h"

#include "ColumnsDelegates/HeaderDelegate.h"
#include "ColumnsDelegates/MultDelegate.h"
#include "ColumnsDelegates/CurveStyleDelegate.h"
ColumnsProperties::ColumnsProperties(DataFromFile* dataFromFile, Canvas* canvas, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ColumnsProperties),
    dataFromFile(dataFromFile)
{
    ui->setupUi(this);
    ui->tableView->setModel(new ColumnsModel(dataFromFile, canvas));
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this,          SLOT(clickToTableView(QModelIndex)));
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), ui->tableView, SLOT(edit(QModelIndex)));
    ui->tableView->setItemDelegateForColumn(0, new HeaderDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(3, new MultDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(4, new CurveStyleDelegate(ui->tableView));
}

ColumnsProperties::~ColumnsProperties()
{
    delete ui->tableView->model();
    delete ui;
}

void ColumnsProperties::detach()
{
    static_cast<ColumnsModel*>(ui->tableView->model())->detach();
}

QString ColumnsProperties::getPathToFile() const
{
    return dataFromFile->getPathToFile();
}

#include <QXmlStreamWriter>
void ColumnsProperties::save(QXmlStreamWriter& out, QString projectName) const
{
    static_cast<ColumnsModel*>(ui->tableView->model())->save(out, projectName);
}

//Read from xml
void ColumnsProperties::read(const DataFromProject& dataFromProject)
{
    static_cast<ColumnsModel*>(ui->tableView->model())->read(dataFromProject);
}

//Replace data
void ColumnsProperties::replace(DataFromFile* dataFromFile)
{
    static_cast<ColumnsModel*>(ui->tableView->model())->replace(dataFromFile);
    dataFromFile = dataFromFile;

}

void ColumnsProperties::clickToTableView(const QModelIndex& index)
{
    if(!index.isValid()){
        return;
    }
    if(index.column() == 1 || index.column() == 2){
        ui->tableView->model()->setData(index, QVariant(), Qt::EditRole);
    }
}
