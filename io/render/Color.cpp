#include "Color.hpp"

namespace io
{

Color Color::black = { 0, 0, 0 };
Color Color::white = { 255, 255, 255 };
Color Color::red = { 255, 0, 0 };
Color Color::green = { 0, 255, 0 };
Color Color::blue = { 0, 0, 255 };

Color::Color(float red, float green, float blue, float alpha) :
    r(red), g(green), b(blue), a(alpha) {}

Color::Color(int red, int green, int blue, int alpha) :
    r(red / 255.0f), g(green / 255.0f), b(blue / 255.0f), a(alpha / 255.0f) {}

Color::Color(const std::initializer_list<float> &components)
{
    operator=(components);
}

Color::Color(const std::initializer_list<int> &components)
{
    operator=(components);
}

Color::Color(const ALLEGRO_COLOR &color)
{
    operator=(color);
}

Color::Color(const Color &color)
{
    operator=(color);
}

Color& Color::operator=(const std::initializer_list<float> &components)
{
    std::initializer_list<float>::const_iterator it = components.begin();

    if (components.size() < 4) {
        a = 1.0f;
    }

    switch (components.size()) {
        case 4: a = *(it + 3);
        case 3: b = *(it + 2);
        case 2: g = *(it + 1);
        case 1: r = *it;
    }

    return *this;
}

Color& Color::operator=(const std::initializer_list<int> &components)
{
    std::initializer_list<int>::const_iterator it = components.begin();

    if (components.size() < 4) {
        a = 255;
    }

    switch (components.size()) {
        case 4: a = *(it + 3) / 255.0f;
        case 3: b = *(it + 2) / 255.0f;
        case 2: g = *(it + 1) / 255.0f;
        case 1: r = *it / 255.0f;
    }

    return *this;
}
    
Color& Color::operator=(const ALLEGRO_COLOR &color)
{
    al_unmap_rgba_f(color, &r, &g, &b, &a);
    return *this;
}

Color& Color::operator=(const Color &color)
{
    if (this != &color) {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }
    return *this;
}

ALLEGRO_COLOR Color::ToAllegroColor() const
{
    return al_map_rgba_f(r, g, b, a);
}

}