#ifndef RECENTLYPROJECTPATHS_H
#define RECENTLYPROJECTPATHS_H

#include <QActionGroup>

class RecentlyProjectPaths : public QActionGroup
{
    Q_OBJECT
public:
    explicit RecentlyProjectPaths(QObject* parent = 0);
    void update(QMenu* projectMenu);
public slots:
    void appendPath(const QString& pathToPro);
private:
    void clear();
    void fill(QMenu* projectMenu);
    void write(const QStringList& recenlyProPaths);
    QStringList getExistPaths() const;
    QString reducePath(const QString& path) const;
};

#endif // RECENTLYPROJECTPATHS_H
