#pragma once

#include "Core.h"

namespace io
{

/*BEGIN*/

template <typename T>
class Region
{
public:
    Vector<T> pos;
    Size<T> size;
    
    Region(T x, T y, T w, T h) : pos(x, y), size(w, h) {}
    Region(Vector<T> pos, Size<T> size) : pos(pos), size(size) {}

    T x() const { return pos.x; }
    T y() const { return pos.y; }
    T w() const { return size.w; }
    T h() const { return size.h; }
    T left() const { return x(); }
    T right() const { return x() + w(); }
    T top() const { return y(); }
    T bottom() const { return y() + h(); }
    Vector<T> top_left() const { return Vector<T>(left(), top()); }
    Vector<T> top_right() const { return Vector<T>(right(), top()); }
    Vector<T> bottom_left() const { return Vector<T>(left(), bottom()); }
    Vector<T> bottom_right() const { return Vector<T>(right(), bottom()); }
    T center_x() const { return x() + w() / 2; }
    T center_y() const { return y() + h() / 2; }
    Vector<T> center() const { return Vector<T>(center_x(), center_y()); }
    
    bool contains(T x, T y) const
    {
        return !(x < left() || x > right() || y < top() || y > bottom());
    }
    
    bool contains(const Vector<T>& v) const
    {
        return contains(v.x, v.y);
    }
    
    bool contains(const Region<T>& r) const
    {
        return contains(r.left(), r.top()) && contains(r.right(), r.bottom());
    }
    
    bool intersects(T x0, T y0, T x1, T y1) const
    {
        return !(x0 > right() || x1 < left() || y0 > bottom() || y1 < top());
    }
    
    bool intersects(const Region<T>& r) const
    {
        return intersects(r.left(), r.top(), r.right(), r.bottom());
    }
    
    bool intersects(const Vector<T>& v, T radius) const
    {
        return false;
    }
    
    std::string to_string() const
    {
        std::stringstream ss;
        ss << "((" << left() << "," + top() << "),(" << right() << "," << bottom() << "))";
        return ss.str();
    }
};

using Region2f = Region<float>;
using Region2i = Region<int>;

/*END*/

} // namespace io