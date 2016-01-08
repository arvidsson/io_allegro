#pragma once

#include "MathHelper.hpp"
#include <initializer_list>
#include <vector>
#include <string>
#include <sstream>

namespace io
{

template <typename T> class Vector
{
public:
    Vector(T x = 0, T y = 0) : x(x), y(y) {}
    Vector(const Vector<T> &v) = default;
    Vector<T>& operator=(const Vector<T> &v) = default;

    Vector<T>& operator=(const std::initializer_list<T> &coords)
    {
        typename std::initializer_list<T>::const_iterator it = coords.begin();
        switch (coords.size()) {
        case 2: y = *(it + 1);
        case 1: x = *it;
        }
        return *this;
    }

    Vector(const std::vector<T> &v)
    {
        x = v[0];
        y = v[1];
    }

    Vector<T>& operator=(const std::vector<T> &v)
    {
        x = v[0];
        y = v[1];
        return *this;
    }

    bool operator==(const Vector<T> &v) const
    {
        return x == v.x && y = v.y;
    }

    bool IsEqual(const Vector<T> &v, const T epsilon = MathHelper<T>::AlmostZero) const
    {
        return MathHelper<T>::IsEqual(x, v.x, epsilon) && MathHelper<T>::IsEqual(y, v.y, epsilon);
    }

    bool operator!=(const Vector<T> &v) const
    {
        return !(operator==(v));
    }

    friend Vector<T> operator+(const Vector<T> &v1, const Vector<T> &v2)
    {
        return Vector<T>(v1.x + v2.x, v1.y + v2.y);
    }

    Vector<T>& operator+=(const Vector<T> &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    friend Vector<T> operator-(const Vector<T> &v1, const Vector<T> &v2)
    {
        return Vector<T>(v1.x - v2.x, v1.y - v2.y);
    }

    Vector<T> operator-() const
    {
        return Vector<T>(-x, -y);
    }

    Vector<T>& operator-=(const Vector<T> &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector<T> operator*(T f) const
    {
        return Vector<T>(x * f, y * f);
    }

    Vector<T>& operator*=(T f)
    {
        x *= f;
        y *= f;
        return *this;
    }

    Vector<T> operator/(T f) const
    {
        return Vector<T>(x / f, y / f);
    }

    Vector<T>& operator/=(T f)
    {
        x /= f;
        y /= f;
        return *this;
    }

    T GetX() const { return x; }
    T GetY() const { return y; }

    T GetDotProduct(const Vector<T> &v) const
    {
        return x * v.x + y * v.y;
    }

    T GetCrossProduct(const Vector<T> &v) const
    {
        return x * v.y - y * v.x;
    }

    T GetLength() const
    {
        return std::sqrt(x * x + y * y);
    }

    T GetLengthSquared() const
    {
        return x * x + y * y;
    }

    void Normalize()
    {
        T l = GetLength();
        if (l) {
            x /= l;
            y /= l;
        }
    }

    Vector<T> GetNormalized() const
    {
        T l = GetLength();
        return l ? Vector<T>(x / l, y / l) : Vector<T>();
    }

    Vector<T> GetPolar(T angle, T length) const
    {
        return Vector<T>(length * std::cos(angle), length * std::sin(angle));
    }

    T GetMagnitude() const
    {
        return GetLength();
    }

    T GetDirection() const
    {
        return std::atan2(y, x);
    }

    T GetAngle() const
    {
        return GetDirection();
    }

    T DistanceTo(const Vector<T> &v)
    {
        T dx = v.x - x;
        T dy = v.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "(" << GetX() << "," << GetY() << ")";
        return ss.str();
    }

    T x, y;
};

template <class T> Vector<T> MakeVector(T x, T y)
{
    return Vector<T>(x, y);
}

using int2 = Vector<int>;
using float2 = Vector<float>;
using double2 = Vector<double>;

}