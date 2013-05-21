#include "StylesEditor.h"
#include "ui_StylesEditor.h"
#include "../Delegate/Delegate.h"
#include "../Delegate/TextDelegate.h"

StylesEditor::StylesEditor(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::StylesEditor),
    showAfterClosing(0)
{
    ui->setupUi(this);
    restoreSettings();
    ui->toolButton_6->hide();
    connect(ui->toolButton_7, SIGNAL(clicked()),            this, SLOT(setNextStylesGroup()));
    connect(ui->treeView,     SIGNAL(clicked(QModelIndex)), this, SLOT(editTreeItem(QModelIndex)));
    connect(ui->toolButton_4, SIGNAL(clicked()),            this, SLOT(removeCurrentStyle()));
    connect(ui->toolButton_5, SIGNAL(clicked()),            this, SLOT(insertNewStyle()));
    connect(ui->toolButton,   SIGNAL(clicked()),            this, SLOT(exportTo()));
    connect(ui->toolButton_2, SIGNAL(clicked()),            this, SLOT(import()));
    connect(ui->toolButton_6, SIGNAL(clicked()),            this, SLOT(saveModel()));
    ui->treeView->setItemDelegateForColumn(1, new Delegate(ui->treeView));
    ui->treeView->setItemDelegateForColumn(0, new TextDelegate(ui->treeView));
    setTitle();
}

StylesEditor::~StylesEditor()
{
    saveSettings();
    delete ui->treeView->model();
    delete ui;
}

void StylesEditor::retranslate()
{
    ui->retranslateUi(this);
}

#include <QMdiSubWindow>
void StylesEditor::showEditor(QWidget* widget)
{
    showAfterClosing = widget;
    show();
}

void StylesEditor::setNextStylesGroup()
{
    modelType = modelType == Model::PLOT_STYLE_MODEL ? Model::CURVE_STYLE_MODEL : Model::PLOT_STYLE_MODEL;
    delete model;
    setTreeModel();
    setTitle();
}

#include "../Item/Item.h"
#include <QFontDialog>
#include <QColorDialog>
void StylesEditor::editTreeItem(const QModelIndex& index)
{
    Item* item = Item::item(index);
    setEnableInsertRemoveActions(item->isStyleName());
    if(item->isEditable(index)){
        ui->treeView->edit(index);
        return;
    }
    if(!index.column()) return;
    if(item->isStyleFont()){
        bool ok;
        QFont font = QFontDialog::getFont(&ok, item->getValue().value<QFont>(), this, tr("Select font, please."));
        if(ok) ui->treeView->model()->setData(index, font, Qt::EditRole);
        return;
    }
    if(item->isStyleColor()){
        QColor color = QColorDialog::getColor(item->getValue().value<QColor>(), this, tr("Select colour, please."));
        if(color != QColor()) ui->treeView->model()->setData(index, color, Qt::EditRole);
    }
}

void StylesEditor::insertNewStyle()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    ui->treeView->model()->insertRow(index.row()+1, index.parent());
}

void StylesEditor::removeCurrentStyle()
{
    if(ui->treeView->children().isEmpty()) return;
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    ui->treeView->model()->removeRow(index.row() == -1 ? 0 : index.row(), index.parent());
}

void StylesEditor::setTreeModel()
{
    model = Model::make(modelType);
    connect(model, SIGNAL(dataChanged()), ui->toolButton_6, SLOT(show()));
    connect(ui->toolButton_3, SIGNAL(clicked()), this, SLOT(setTreeModel()));
    ui->treeView->setModel(model);
    ui->toolButton_6->hide();
    setEnableInsertRemoveActions(true);
}

#include <QFileDialog>
#include <QXmlStreamReader>
void StylesEditor::import()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Import the styles"), importPath, "*.ini");
    if(path.isEmpty()) return;
    QFile file(path);
    if(!file.open(QFile::ReadOnly)) return;
    importPath = path;
    QXmlStreamReader in(&file);
    in.readNext(); //read <StartDocument>.
        model->read(in);
    ui->toolButton_6->show();
}

void StylesEditor::exportTo()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Export the styles"), exportPath, "*.ini");
    if(path.isEmpty()) return;
    QFile file(path);
    if(!file.open(QFile::WriteOnly)) return;
    exportPath = path;
    QXmlStreamWriter out(&file);
    out.setAutoFormatting(true);
    out.writeStartDocument();
        model->save(out);
    out.writeEndDocument();
}

#include "../StylesCurve.h"
#include "../../Canvas/Curves/PlotCurve.h"
void StylesEditor::saveModel()
{
    model->save();
    if(modelType == Model::CURVE_STYLE_MODEL){
        StylesCurve::getInstance()->update();
        PlotCurve::updateStyles();
    }else
        if(modelType == Model::PLOT_STYLE_MODEL){
            emit setCurvesStyle();
        }
    emit replot();
}


void StylesEditor::closeEvent(QCloseEvent *evt)
{
    QDialog::closeEvent(evt);
    if(showAfterClosing){
        showAfterClosing->show();
        showAfterClosing = 0;
    }
}

#include <QSettings>
void StylesEditor::saveSettings()
{
    QSettings settings;
    settings.setValue("Widget settings/StylesEditor/Geometry", saveGeometry());
    settings.setValue("Widget settings/StylesEditor/_model_type", modelType);
    settings.setValue("Widget settings/StylesEditor/TreeViewColumnWidth", ui->treeView->columnWidth(0));
    settings.setValue("Widget settings/StylesEditor/ImportPath", importPath);
    settings.setValue("Widget settings/StylesEditor/ExportPath", exportPath);
}

void StylesEditor::restoreSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("Widget settings/StylesEditor/Geometry").toByteArray());
    modelType = (Model::Type) settings.value("Widget settings/StylesEditor/_model_type").toInt();
    setTreeModel();
    int column_width = settings.value("Widget settings/StylesEditor/TreeViewColumnWidth").toInt();
    if(column_width)ui->treeView->setColumnWidth(0, column_width);
    importPath = settings.value("Widget settings/StylesEditor/ImportPath").toString();
    exportPath = settings.value("Widget settings/StylesEditor/ExportPath").toString();
}

void StylesEditor::setTitle()
{
    switch(modelType){
        case Model::PLOT_STYLE_MODEL  : setWindowTitle(tr("The styles' group is plot"));  return;
        case Model::CURVE_STYLE_MODEL : setWindowTitle(tr("The styles' group is curve")); return;
    }
}

void StylesEditor::setEnableInsertRemoveActions(bool enable)
{
    ui->toolButton_4->setEnabled(enable);
    ui->toolButton_5->setEnabled(enable);
}
