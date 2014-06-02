#include "Settings.h"


Settings* Settings::instance = nullptr;

Settings::Settings(const QString& pathToSettingsFile):
    settings(pathToSettingsFile, QSettings::IniFormat)
{
}

void Settings::create(const QString& pathToSettingsFile)
{
    if(instance){
        destroy();
    }
    instance = new Settings(pathToSettingsFile);
}

void Settings::destroy()
{
    delete instance;
    instance = nullptr;
}

Settings* Settings::obj()
{
    return instance;
}

QVariant Settings::get(const QString& key, const QVariant& defaultValue)
{
    return settings.value(key, defaultValue);
}

void Settings::set(const QString& key, const QVariant& value)
{
    settings.setValue(key, value);
}

QSettings& Settings::get()
{
    return settings;
}
