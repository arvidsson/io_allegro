#pragma once

#include "Core.h"
#include "Math.h"

namespace io
{

/*BEGIN*/

template <class Derived, typename T, int N>
class VectorBase;

template <class Derived, typename T>
class VectorBase<Derived, T, 2>
{
protected:
    T values[2];
    VectorBase(T v0, T v1) : values{v0, v1} {}
    
    bool operator==(const Derived& v) const 
    {
        return values[0] == v.values[0] && values[1] == v.values[1];
    }
    
    bool operator!=(const Derived& v) const 
    {
        return !(operator==(v));
    }
    
    bool is_equal(const Derived& v, T epsilon = 0.001) const 
    {
        return Math<T>::is_equal(values[0], v.values[0], epsilon) && Math<T>::is_equal(values[1], v.values[1], epsilon);
    }
    
    friend Derived operator+(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] + v2.values[0], v1.values[1] + v2.values[1]};
    }

    Derived& operator+=(const Derived& v)
    {
        values[0] += v.values[0];
        values[1] += v.values[1];
        return static_cast<Derived&>(*this);
    }
    
    friend Derived operator-(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] - v2.values[0], v1.values[1] - v2.values[1]};
    }

    Derived operator-() const
    {
        return Derived{-values[0], -values[1]};
    }

    Derived& operator-=(const Derived& v)
    {
        values[0] -= v.values[0];
        values[1] -= v.values[1];
        return static_cast<Derived&>(*this);
    }

    Derived operator*(T f) const
    {
        return Derived{values[0] * f, values[1] * f};
    }

    Derived& operator*=(T f)
    {
        values[0] *= f;
        values[1] *= f;
        return static_cast<Derived&>(*this);
    }

    Derived operator/(T f) const
    {
        return Derived{values[0] / f, values[1] / f};
    }

    Derived& operator/=(T f)
    {
        values[0] /= f;
        values[1] /= f;
        return static_cast<Derived&>(*this);
    }
};

template <class Derived, typename T>
class VectorBase<Derived, T, 3>
{
protected:
    T values[3];
    VectorBase(T v0, T v1, T v2) : values{v0, v1, v2} {}
    
    bool operator==(const Derived& v) const 
    {
        return values[0] == v.values[0] && values[1] == v.values[1] && values[2] == v.values[2];
    }
    
    bool operator!=(const Derived& v) const 
    {
        return !(operator==(v));
    }
    
    bool is_equal(const Derived& v, T epsilon = 0.001) const 
    {
        return Math<T>::is_equal(values[0], v.values[0], epsilon) && Math<T>::is_equal(values[1], v.values[1], epsilon && Math<T>::is_equal(values[2], v.values[2], epsilon));
    }
    
    friend Derived operator+(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] + v2.values[0], v1.values[1] + v2.values[1], v1.values[2] + v2.values[2]};
    }

    Derived& operator+=(const Derived& v)
    {
        values[0] += v.values[0];
        values[1] += v.values[1];
        values[2] += v.values[2];
        return static_cast<Derived&>(*this);
    }
    
    friend Derived operator-(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] - v2.values[0], v1.values[1] - v2.values[1], v1.values[2] - v2.values[2]};
    }

    Derived operator-() const
    {
        return Derived{-values[0], -values[1], -values[2]};
    }

    Derived& operator-=(const Derived& v)
    {
        values[0] -= v.values[0];
        values[1] -= v.values[1];
        values[2] -= v.values[2];
        return static_cast<Derived&>(*this);
    }

    Derived operator*(T f) const
    {
        return Derived{values[0] * f, values[1] * f, values[2] * f};
    }

    Derived& operator*=(T f)
    {
        values[0] *= f;
        values[1] *= f;
        values[2] *= f;
        return static_cast<Derived&>(*this);
    }

    Derived operator/(T f) const
    {
        return Derived{values[0] / f, values[1] / f, values[2] / f};
    }

    Derived& operator/=(T f)
    {
        values[0] /= f;
        values[1] /= f;
        values[2] /= f;
        return static_cast<Derived&>(*this);
    }
};

template <class Derived, typename T>
class VectorBase<Derived, T, 4>
{
protected:
    T values[4];
    VectorBase(T v0, T v1, T v2, T v3) : values{v0, v1, v2, v3} {}
    
    bool operator==(const Derived& v) const 
    {
        return values[0] == v.values[0] && values[1] == v.values[1] && values[2] == v.values[2] && values[3] == v.values[3];
    }
    
    bool operator!=(const Derived& v) const 
    {
        return !(operator==(v));
    }
    
    bool is_equal(const Derived& v, T epsilon = 0.001) const 
    {
        return Math<T>::is_equal(values[0], v.values[0], epsilon) && Math<T>::is_equal(values[1], v.values[1], epsilon && Math<T>::is_equal(values[2], v.values[2], epsilon) && Math<T>::is_equal(values[3], v.values[3], epsilon));
    }
    
    friend Derived operator+(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] + v2.values[0], v1.values[1] + v2.values[1], v1.values[2] + v2.values[2], v1.values[3] + v2.values[3]};
    }

    Derived& operator+=(const Derived& v)
    {
        values[0] += v.values[0];
        values[1] += v.values[1];
        values[2] += v.values[2];
        values[3] += v.values[3];
        return static_cast<Derived&>(*this);
    }
    
    friend Derived operator-(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] - v2.values[0], v1.values[1] - v2.values[1], v1.values[2] - v2.values[2], v1.values[3] - v2.values[3]};
    }

    Derived operator-() const
    {
        return Derived{-values[0], -values[1], -values[2], -values[3]};
    }

    Derived& operator-=(const Derived& v)
    {
        values[0] -= v.values[0];
        values[1] -= v.values[1];
        values[2] -= v.values[2];
        values[3] -= v.values[3];
        return static_cast<Derived&>(*this);
    }

    Derived operator*(T f) const
    {
        return Derived{values[0] * f, values[1] * f, values[2] * f, values[3] * f};
    }

    Derived& operator*=(T f)
    {
        values[0] *= f;
        values[1] *= f;
        values[2] *= f;
        values[3] *= f;
        return static_cast<Derived&>(*this);
    }

    Derived operator/(T f) const
    {
        return Derived{values[0] / f, values[1] / f, values[2] / f, values[3] / f};
    }

    Derived& operator/=(T f)
    {
        values[0] /= f;
        values[1] /= f;
        values[2] /= f;
        values[3] /= f;
        return static_cast<Derived&>(*this);
    }
};

/*END*/

} // namespace io