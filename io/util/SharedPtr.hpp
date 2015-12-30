#pragma once

#include <memory>

namespace io
{

/*
    Useful template in order to encapsulate C objects in an object that is a shared pointer at once.
*/
template <class T>
class SharedPtr : public std::shared_ptr<T>
{
protected:
    SharedPtr() {}
    template <class Deleter> SharedPtr(T *object, Deleter deleter) : std::shared_ptr<T>(object, deleter) {}
    SharedPtr(T *object) : std::shared_ptr<T>(object) {}
    SharedPtr(const std::shared_ptr<T> &ptr) : std::shared_ptr<T>(ptr) {}
};

}