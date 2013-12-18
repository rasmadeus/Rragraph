#ifndef QUICKVIEWER_H
#define QUICKVIEWER_H

#include <QtQuick/QQuickView>

class QuickViewer : public QQuickView
{
    Q_OBJECT

public:
    explicit QuickViewer(QWindow *parent = 0);
    virtual ~QuickViewer();

    void setMainQmlFile(const QString &file);
    void addImportPath(const QString &path);

    void showExpanded();

private:
    class QuickViewerPrivate *d;
};

#endif // QUICKVIEWER_H
