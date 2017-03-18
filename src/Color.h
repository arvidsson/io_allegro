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
    
    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);
    Color(int r, int g, int b, int a);
    Color& operator=(const Color& c);
    Color(const ALLEGRO_COLOR& color);
    Color& operator=(const ALLEGRO_COLOR& color);
    
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
    
    ALLEGRO_COLOR to_allegro_color() const;
    std::string to_string() const;
};

/*END*/

} // namespace io