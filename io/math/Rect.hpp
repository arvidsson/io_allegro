#pragma once

#include "Vector.hpp"
#include "Size.hpp"
#include "MathHelper.hpp"
#include <initializer_list>
#include <string>
#include <sstream>

namespace io
{

template <class T> class Rect
{
public:
    Rect(T x = 0, T y = 0, T w = 0, T h = 0) : position(x, y), size(w, h) {}
    Rect(const Vector<T> &position, const Size<T> &size) : position(position), size(size) {}
    Rect(const Rect<T> &rect) = default;
    Rect<T>& operator=(const Rect<T> &rect) = default;

    Rect(const Vector<T> &topLeft, const Vector<T> &bottomRight)
    {
        position = topLeft;
        size = { bottomRight.x - topLeft.x, bottomRight.y - topLeft.y };
    }

    // {x, y, w, h}
    Rect<T>& operator=(const std::initializer_list<T> &coords)
    {
        typename std::initializer_list<T>::const_iterator it = coords.begin();
        switch (coords.size()) {
        case 4: size.h = *(it + 3);
        case 3: size.w = *(it + 2);
        case 2: position.y = *(it + 1);
        case 1: position.x = *it;
        }

        if (coords.size() > 3) {
            size.h = position.y + sizeh;
        }
        else {
            size.h = 0;
        }

        if (coords.size() > 2) {
            size.w = position.x + size.w;
        }
        else {
            size.w = 0;
        }

        return *this;
    }

    T GetX() const
    {
        return position.x;
    }

    T GetY() const
    {
        return position.y;
    }

    Vector<T> GetPosition() const
    {
        return position;
    }

    T GetWidth() const
    {
        return size.w;
    }

    T GetHeight() const
    {
        return size.h;
    }

    Size<T> GetSize() const
    {
        return size;
    }

    T GetArea() const
    {
        return size.GetArea();
    }

    T Left() const
    {
        return position.x;
    }

    T Right() const
    {
        return position.x + size.w;
    }

    T Top() const
    {
        return position.y;
    }

    T Bottom() const
    {
        return position.y + size.h;
    }

    Vector<T> TopLeft() const
    {
        return Vector<T>(Left(), Top());
    }

    Vector<T> BottomRight() const
    {
        return Vector<T>(Right(), Bottom());
    }

    T GetCenterX() const
    {
        return position.x + (size.w / 2);
    }

    T GetCenterY() const
    {
        return position.y + (size.h / 2);
    }

    Vector<T> GetCenter() const
    {
        return Vector<T>(GetCenterX(), GetCenterY());
    }

    void MoveTo(T x, T y)
    {
        position = { x, y };
    }

    void MoveBy(T dx, T dy)
    {
        position.x += dx;
        position.y += dy;
    }

    void SetSize(T w, T h)
    {
        size = { w, h };
    }

    void GrowBy(T dw, T dh)
    {
        size.w += dw;
        size.h += dh;
    }

    void ShrinkBy(T dw, T dh)
    {
        size.w -= dw;
        size.h -= dh;
    }

    // Returns true if the rectangle contains a point.
    bool Contains(T x, T y) const
    {
        return !(x < Left() || x > Right() || y < Top() || y > Bottom());
    }

    // Returns true if the rectangle contains a point.
    bool Contains(const Vector<T> &point) const
    {
        return Contains(point.x, point.y);
    }

    // Returns true if the rectangle contains another rectangle.
    bool Contains(const Rect<T> &rect) const
    {
        return Contains(rect.TopLeft()) && Contains(rect.BottomRight());
    }

    // Returns true if the rectangle intersects another rectangle.
    bool Intersects(T l, T t, T r, T b) const
    {
        return !(l > Right() || r < Left() || t > Bottom() || b < Top());
    }

    // Returns true if the rectangle intersects another rectangle.
    bool Intersects(const Rect<T> &rect) const
    {
        return Intersects(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    }

    // Return a string representation of the rectangle (position and size).
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "((" << Left() << "," + Top() << "),(" << GetWidth() << "x" << GetHeight() << "))";
        return ss.str();
    }

    Vector<T> position;
    Size<T> size;
};

template <class T> Rect<T> MakeRect(T x, T y, T w, T h)
{
    return Rect<T>(x, y, w, h);
}

template <class T> Rect<T> MakeRect(const Vector<T> &position, const Size<T> &size)
{
    return Rect<T>(position, size);
}

}