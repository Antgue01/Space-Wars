#include "EntityFactory.h"
template <typename T>
T* EntityFactory<T>::create()
{
    return new T();
}
template <typename T>
T* EntityFactory<T>::create(T t){
    return new T(t);
}