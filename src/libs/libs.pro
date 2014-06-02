TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    Settings \
    FilesLoader \
    PreCustomizedQwt \
    CurvesManager \
    VersionConverter

TRANSLATIONS += $$PWD/../apps/rragraph/ts/libs_app_ru.ts
