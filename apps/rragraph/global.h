#ifndef GLOBAL_H
#define GLOBAL_H

#define PRIVATE_DATA \
    class PrivateData; \
    PrivateData* d;

#define SINGLETON_HEADER(Class, Parent) \
    Q_DISABLE_COPY(Class) \
    explicit Class(Parent* parent = 0); \
    static Class* instance; \
public: \
    static void make(Parent* parent = 0); \
    static Class* getInstance();

#define SINGLETON_IMPLEMENTATION(Class, Parent) \
Class* Class::instance = nullptr; \
Class* Class::getInstance(){ \
    return instance; \
} \
void Class::make(Parent* parent){ \
    instance = new Class(parent); \
}

#endif // GLOBAL_H


