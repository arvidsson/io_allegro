#pragma once

#include "Core.h"
#include "VectorBase.h"

namespace io
{

/*BEGIN*/

template <typename T>
class Size : public VectorBase<Size<T>, T, 2>
{
    using Base = VectorBase<Size<T>, T, 2>;
    
public:
    T& w;
    T& h;
    
    Size(T w = T(), T h = T()) : Base(w, h), w(Base::values[0]), h(Base::values[1]) {}
    Size& operator=(const Size& s) { w = s.w; h = s.h; return *this; }
    
    using Base::operator==;
    using Base::operator!=;
    using Base::is_equal;
    using Base::operator+=;
    using Base::operator-;
    using Base::operator-=;
    using Base::operator*;
    using Base::operator*=;
    using Base::operator/;
    using Base::operator/=;
    
    std::string to_string() const
    {
        std::stringstream ss;
        ss << "(" << w << "x" << h << ")";
        return ss.str();
    }
};

using Size2i = Size<int>;
using Size2f = Size<float>;

/*END*/

} // namespace io