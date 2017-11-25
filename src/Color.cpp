#include "Color.h"

namespace io
{

/*BEGIN*/

Color::Color(float r, float g, float b, float a) : Base(r, g, b, a), r(Base::values[0]), g(Base::values[1]), b(Base::values[2]), a(Base::values[3])
{
}

Color::Color(int r, int g, int b, int a) : Base(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f), r(Base::values[0]), g(Base::values[1]), b(Base::values[2]), a(Base::values[3])
{
}

Color& Color::operator=(const Color& c)
{
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
    return *this;
}

Color::Color(const ALLEGRO_COLOR& color) : Color()
{
    operator=(color);
}

Color& Color::operator=(const ALLEGRO_COLOR& color)
{
    al_unmap_rgba_f(color, &r, &g, &b, &a);
    return *this;
}

ALLEGRO_COLOR Color::to_allegro_color() const
{
    return al_map_rgba_f(r, g, b, a);
}

std::string Color::to_string() const
{
    std::stringstream ss;
    ss << "(" << r << "," << g << "," << b << "," << a << ")";
    return ss.str();
}

/*END*/

} // namespace io