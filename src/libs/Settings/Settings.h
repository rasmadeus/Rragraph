#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QVariant>
#include <utility>

class Settings
{
public:
    static Settings* obj();
    QVariant get(const QString& key, const QVariant& defaultValue = QVariant());
    void set(const QString& key, const QVariant& value);
    static void create(const QString& pathToSettingsFile);
    static void destroy();
    QSettings& get();
private:
    static Settings* instance;
    QSettings settings;
    Settings(const QString& pathToSettingsFile);
    Settings(const Settings&);
    Settings& operator = (const Settings&);
};

#endif // SETTINGS_H
