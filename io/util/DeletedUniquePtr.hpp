#pragma once

#include <functional>
#include <memory>

namespace io
{

/*
    Alias to easily define deleted unique pointers:

    Examples:
    DeletedUniquePtr<Foo> foo(new Foo(), [](Foo* f) { custom_deleter(f); });
    DeletedUniquePtr<FILE> file(fopen("file.txt", "r"), [](FILE* f) { fclose(f); });
*/
template<typename T>
using DeletedUniquePtr = std::unique_ptr<T, std::function<void(T*)>>;

}