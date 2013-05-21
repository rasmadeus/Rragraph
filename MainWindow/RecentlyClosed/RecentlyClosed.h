#ifndef RECENTLYCLOSED_H
#define RECENTLYCLOSED_H

class QMenu;
class QSettings;
#include <QObject>

class RecentlyClosed : public QObject
{
    Q_OBJECT
public:
    explicit RecentlyClosed(QMenu* menu, QObject *parent = 0);
    void fill(QSettings& settings);
    void savePathOfProject(const QString& projectName);
public slots:
    void removeNonexistentPaths();
private:
    QList<QString> readRecentlyClosed(QSettings& settings);
    void writeRecentlyClosed(const QList<QString>& paths, QSettings& settings);
    void updateRecentlyClosedMenu(const QList<QString>& paths);
signals:
    void readProjectFrom(QString);
private slots:
    void recentlyClosedActionTriggered();
private:
    QMenu* menu;
};

#endif // RECENTLYCLOSED_H
