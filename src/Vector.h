#pragma once

#include "Core.h"
#include "VectorBase.h"

namespace io
{

/*BEGIN*/

template <typename T>
class Vector : public VectorBase<Vector<T>, T, 2>
{
    using Base = VectorBase<Vector<T>, T, 2>;
    
public:
    T& x;
    T& y;
    
    Vector(T x = T(), T y = T()) : Base(x, y), x(Base::values[0]), y(Base::values[1]) {}
    Vector& operator=(const Vector& v) { x = v.x; y = v.y; return *this; }
    
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
    
    T dot_product(const Vector& v) const
    {
        return x * v.x + y * v.y;
    }
    
    T cross_product(const Vector& v) const
    {
        return x * v.y - y * v.x;
    }
    
    T length() const
    {
        return std::sqrt(x * x + y * y);
    }
    
    T length_squared() const
    {
        return x * x + y * y;
    }
    
    void normalize()
    {
        T l = length();
        if (l) {
            x /= l;
            y /= l;
        }
    }

    Vector normalized() const
    {
        T l = length();
        return l ? Vector{x / l, y / l} : Vector();
    }

    Vector polar(T angle, T length) const
    {
        return Vector{length * std::cos(angle), length * std::sin(angle)};
    }

    T magnitude() const
    {
        return length();
    }

    T direction() const
    {
        return std::atan2(y, x);
    }

    T angle() const
    {
        return direction();
    }

    T distance_to(const Vector& v)
    {
        T dx = v.x - x;
        T dy = v.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << "(" << x << "," << y << ")";
        return ss.str();
    }
};

using Vector2i = Vector<int>;
using Vector2f = Vector<float>;

/*END*/

} // namespace io