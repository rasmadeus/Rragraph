#ifndef HEADERSVIEW_H
#define HEADERSVIEW_H

class FilesModel;
class HeadersModel;
#include <QWidget>

namespace Ui {
class HeadersView;
}

class HeadersView : public QWidget
{
    Q_OBJECT
    Ui::HeadersView *ui;
    FilesModel* filesModel;
    HeadersModel* headersModel;
public:
    explicit HeadersView(QWidget *parent = 0);
    ~HeadersView();
private slots:
    void wasAdded(int iFile);
    void wasRemoved(int iFile);
    void resetClicked();
};

#endif // HEADERSVIEW_H
