#ifndef STYLESEDITOR_H
#define STYLESEDITOR_H

#include "../Model/Model.h"
#include <QDialog>

namespace Ui {
    class StylesEditor;
}

class StylesEditor : public QDialog
{
    Q_OBJECT

public:
    explicit StylesEditor(QWidget* parent = 0);
    ~StylesEditor();
    void retranslate();
signals:
    void replot();
    void setCurvesStyle();
public slots:
    void showEditor(QWidget* widget);
private slots:
    void setNextStylesGroup();
    void editTreeItem(const QModelIndex& index);
    void insertNewStyle();
    void removeCurrentStyle();
    void setTreeModel();
    void import();
    void exportTo();
    void saveModel();
protected:
    void closeEvent(QCloseEvent* evt);
private:
    void saveSettings();
    void restoreSettings();
    void setTitle();
    void setEnableInsertRemoveActions(bool visible);
private:
    Ui::StylesEditor* ui;
    Model::Type modelType;
    Model* model;
    QWidget* showAfterClosing; //Show widget if this is closing.
    QString exportPath;
    QString importPath;
};

#endif // STYLESEDITOR_H
