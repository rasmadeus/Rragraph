#include "QuickViewer.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>

class QuickViewerPrivate
{
    QString mainQmlFile;
    friend class QuickViewer;
    static QString adjustPath(const QString &path);
};

QString QuickViewerPrivate::adjustPath(const QString &path)
{
#if defined(Q_OS_MAC)
    if (!QDir::isAbsolutePath(path))
        return QString::fromLatin1("%1/../Resources/%2")
                .arg(QCoreApplication::applicationDirPath(), path);
#elif defined(Q_OS_BLACKBERRY)
    if (!QDir::isAbsolutePath(path))
        return QString::fromLatin1("app/native/%1").arg(path);
#elif !defined(Q_OS_ANDROID)
    QString pathInInstallDir =
            QString::fromLatin1("%1/../%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(pathInInstallDir).exists())
        return pathInInstallDir;
    pathInInstallDir =
            QString::fromLatin1("%1/%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(pathInInstallDir).exists())
        return pathInInstallDir;
#endif
    return path;
}

QuickViewer::QuickViewer(QWindow *parent)
    : QQuickView(parent)
    , d(new QuickViewerPrivate())
{
    connect(engine(), SIGNAL(quit()), SLOT(close()));
    setResizeMode(QQuickView::SizeRootObjectToView);
    setIcon(QIcon(":/res/icon.ico"));
}

QuickViewer::~QuickViewer()
{
    delete d;
}

void QuickViewer::setMainQmlFile(const QString& file)
{
    d->mainQmlFile =  QuickViewerPrivate::adjustPath(file);

#ifdef Q_OS_ANDROID
    setSource(QUrl(QLatin1String("assets:/")+d->mainQmlFile));
#else
    setSource(QUrl::fromLocalFile(d->mainQmlFile));
#endif
}

void QuickViewer::addImportPath(const QString &path)
{
    engine()->addImportPath(QuickViewerPrivate::adjustPath(path));
}

void QuickViewer::showExpanded()
{
#if defined(Q_WS_SIMULATOR) || defined(Q_OS_QNX)
    showFullScreen();
#else
    show();
#endif
}
