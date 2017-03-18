#pragma once

#include "Core.h"
#include "VectorBase.h"

namespace io
{

/*BEGIN*/

class Color : public VectorBase<Color, float, 4>
{
    using Base = VectorBase<Color, float, 4>;
    
public:
    float& r;
    float& g;
    float& b;
    float& a;
    
    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f) : Base(r, g, b, a), r(Base::values[0]), g(Base::values[1]), b(Base::values[2]), a(Base::values[3]) {}
    Color(int r, int g, int b, int a) : Base(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f), r(Base::values[0]), g(Base::values[1]), b(Base::values[2]), a(Base::values[3]) {}
    Color& operator=(const Color& c) { r = c.r; g = c.g; b = c.b; a = c.a; return *this; }
    Color(const ALLEGRO_COLOR& color) : Color() { operator=(color); }
    Color& operator=(const ALLEGRO_COLOR& color) { al_unmap_rgba_f(color, &r, &g, &b, &a); return *this; }
    
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
    
    ALLEGRO_COLOR to_allegro_color() const
    {
        return al_map_rgba_f(r, g, b, a);
    }
    
    std::string to_string() const
    {
        std::stringstream ss;
        ss << "(" << r << "," << g << "," << b << "," << a << ")";
        return ss.str();
    }
};

/*END*/

} // namespace io