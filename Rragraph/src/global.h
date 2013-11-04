#ifndef GLOBAL_H
#define GLOBAL_H

#define PRIVATE_DATA \
    class PrivateData; \
    PrivateData* d;

#define SINGLETON_HEADER(Class) \
    Q_DISABLE_COPY(Class) \
    explicit Class(QObject* parent = 0); \
    static Class* instance; \
public: \
    static Class* getInstance(QObject* parent = 0);

#define SINGLETON_IMPLEMENTATION(Class) \
Class* Class::instance = nullptr; \
Class* Class::getInstance(QObject* parent) \
{ \
    if(instance == nullptr){ \
        instance = new Class(parent); \
    } \
    return instance; \
}


#endif // GLOBAL_H


