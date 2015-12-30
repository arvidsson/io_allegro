#pragma once

#include "../util/SharedPtr.hpp"
#include "../math/Vector.hpp"
#include "../math/Size.hpp"
#include <allegro5/allegro.h>
#include <string>

namespace io
{

class Image : public SharedPtr<ALLEGRO_BITMAP>
{
public:
    Image() {}
    Image(std::string filename) : SharedPtr(al_load_bitmap(filename.c_str()), al_destroy_bitmap) {}
    Image(int width, int height) : SharedPtr(al_create_bitmap(width, height), al_destroy_bitmap) {}
    Image(const Size<int> &size) : SharedPtr(al_create_bitmap(size.w, size.h), al_destroy_bitmap) {}
    Image(Image &parent, int x, int y, int width, int height) : SharedPtr(al_create_sub_bitmap(parent.get(), x, y, width, height), al_destroy_bitmap) {}
    Image(Image &parent, const Vector<int> &position, const Size<int> &size) : SharedPtr(al_create_sub_bitmap(parent.get(), position.x, position.y, size.w, size.h), al_destroy_bitmap) {}

    int GetWidth() const { return al_get_bitmap_width(get()); }
    int GetHeight() const { return al_get_bitmap_height(get()); }
    Size<int> GetSize() const { return Size<int>(GetWidth(), GetHeight()); }
};

}