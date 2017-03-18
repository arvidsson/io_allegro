#pragma once

#include "Core.h"
#include "Vector.h"
#include "Size.h"

namespace io
{

/*BEGIN*/

using Bitmap = std::shared_ptr<ALLEGRO_BITMAP>;
using Font = std::shared_ptr<ALLEGRO_FONT>;
using Sound = std::shared_ptr<ALLEGRO_SAMPLE>;
using Music = std::shared_ptr<ALLEGRO_AUDIO_STREAM>;

Bitmap make_bitmap(int width, int height);
Bitmap load_bitmap(std::string filename);
Bitmap cut_bitmap(Bitmap parent, Vector2i pos, Size2i size);
Font load_font(std::string filename, int size);
Sound load_sound(std::string filename);
Music load_music(std::string filename);

class Resources
{
public:
    Bitmap get_bitmap(std::string filename);
    std::vector<Bitmap> get_sub_bitmaps(std::string filename, int width, int height);
    Font get_font(std::string filename, int size);
    Sound get_sound(std::string filename);
    Music get_music(std::string filename);
private:
    std::unordered_map<std::string, Bitmap> bitmaps;
    std::unordered_map<std::string, std::vector<Bitmap>> sub_bitmaps;
    std::unordered_map<std::string, Font> fonts;
    std::unordered_map<std::string, Sound> sounds;
    std::unordered_map<std::string, Music> music;
};

/*END*/

} // namespace io