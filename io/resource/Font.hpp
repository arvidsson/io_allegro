#pragma once

#include "../util/SharedPtr.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

namespace io
{

class Font : public SharedPtr<ALLEGRO_FONT>
{
public:
    Font() {}
    Font(std::string filename, int size) : SharedPtr(al_load_font(filename.c_str(), size, 0), al_destroy_font) {}
    Font(ALLEGRO_FONT *font) : SharedPtr(font, al_destroy_font) {}

    int GetWidth(std::string text) const { return al_get_text_width(get(), text.c_str()); }
    int GetHeight() const { return al_get_font_line_height(get()); }
};

}