#include "Resources.h"

namespace io
{

/*BEGIN*/

Bitmap make_bitmap(int width, int height)
{
    return Bitmap(al_create_bitmap(width, height), al_destroy_bitmap);
}
    
Bitmap load_bitmap(std::string filename)
{
    return Bitmap(al_load_bitmap(filename.c_str()), al_destroy_bitmap);   
}

Bitmap cut_bitmap(Bitmap parent, Vector2i pos, Size2i size)
{
    return Bitmap(al_create_sub_bitmap(parent.get(), pos.x, pos.y, size.w, size.h), al_destroy_bitmap);
}

Font load_font(std::string filename, int size)
{
    return Font(al_load_font(filename.c_str(), size, 0), al_destroy_font);   
}

Sound load_sound(std::string filename)
{
    return Sound(al_load_sample(filename.c_str()), al_destroy_sample);   
}

Music load_music(std::string filename)
{
    return Music(al_load_audio_stream(filename.c_str(), 4, 2048), al_destroy_audio_stream);   
}

Bitmap Resources::get_bitmap(std::string filename)
{
    if (bitmaps.find(filename) != bitmaps.end())
    {
        return bitmaps[filename];
    }

    Bitmap bitmap = load_bitmap(filename);
    if (!bitmap)
    {
        IO_THROW("Failed to load bitmap: %s", filename.c_str());
    }

    bitmaps[filename] = bitmap;
    return bitmap;
}

std::vector<Bitmap> Resources::get_sub_bitmaps(std::string filename, int width, int height)
{
    if (sub_bitmaps.find(filename) != sub_bitmaps.end()) {
        return sub_bitmaps[filename];
    }

    Bitmap bitmap = get_bitmap(filename);
    std::vector<Bitmap> sub_bmps;

    int cols = al_get_bitmap_width(bitmap.get()) / width;
    int rows = al_get_bitmap_height(bitmap.get()) / height;

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            Bitmap sub_bitmap = cut_bitmap(bitmap, { i * width, j * height }, { width, height });
            if (!sub_bitmap)
            {
                IO_THROW("Failed to create sub-bitmaps for: %s", filename.c_str());
            }
            sub_bmps.push_back(sub_bitmap);
        }
    }

    sub_bitmaps[filename] = sub_bmps;
    return sub_bmps;
}

Font Resources::get_font(std::string filename, int size)
{
    std::string font_name = filename + std::to_string(size);
    if (fonts.find(font_name) != fonts.end())
    {
        return fonts[font_name];
    }

    Font font = load_font(filename, size);
    if (!font)
    {
        IO_THROW("Failed to load font: %s (%d)", filename.c_str(), size);
    }

    fonts[font_name] = font;
    return font;
}

Sound Resources::get_sound(std::string filename)
{
    if (sounds.find(filename) != sounds.end())
    {
        return sounds[filename];
    }

    Sound sound = load_sound(filename);
    if (!sound)
    {
        IO_THROW("Failed to load sound: %s", filename.c_str());
    }

    sounds[filename] = sound;
    return sound;
}

Music Resources::get_music(std::string filename)
{
    if (music.find(filename) != music.end())
    {
        return music[filename];
    }

    Music song = load_music(filename);
    if (!song)
    {
        IO_THROW("Failed to load music: %s", filename.c_str());
    }

    al_attach_audio_stream_to_mixer(song.get(), al_get_default_mixer());
    al_set_audio_stream_playing(song.get(), false);

    music[filename] = song;
    return song;
}

/*END*/

} // namespace io