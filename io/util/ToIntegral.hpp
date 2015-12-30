#pragma once

#include <type_traits>

namespace io
{

/*
    Convert enum class to underlying integral type.
    See: http://stackoverflow.com/questions/14589417/can-an-enum-class-be-converted-to-the-underlying-type
*/
template <typename T>
auto ToIntegral(T t) -> typename std::underlying_type<T>::type 
{
    return static_cast<typename std::underlying_type<T>::type>(t);
}

}