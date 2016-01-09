#include "Resources.hpp"
#include "Debug.hpp"
using namespace alcpp;

namespace io
{

Bitmap Resources::GetBitmap(const std::string &filename)
{
    if (bitmaps.find(filename) != bitmaps.end()) {
        return bitmaps[filename];
    }

    Bitmap bitmap(filename);
    if (!bitmap) {
        Throw("Failed to load bitmap: %s", filename.c_str());
    }

    bitmaps[filename] = bitmap;
    return bitmap;
}

/*
Font Resources::GetFont(const std::string &filename, int size)
{
    std::string fontName = filename + std::to_string(size);
    if (fonts.find(fontName) != fonts.end()) {
        return fonts[fontName];
    }

    Font font = Font(filename, size);
    if (!font) {
        Throw("Failed to load font: %s (%d)", filename.c_str(), size);
    }

    fonts[fontName] = font;
    return font;
}

Sound Resources::GetSound(const std::string &filename)
{
    if (sounds.find(filename) != sounds.end()) {
        return sounds[filename];
    }

    Sound sound = Sound(filename);
    if (!sound) {
        Throw("Failed to load sound: %s", filename.c_str());
    }

    sounds[filename] = sound;
    return sound;
}

Music Resources::GetMusic(const std::string &filename)
{
    if (music.find(filename) != music.end()) {
        return music[filename];
    }

    Music song = Music(filename);
    if (!song) {
        Throw("Failed to load music: %s", filename.c_str());
    }

    al_attach_audio_stream_to_mixer(song.get(), al_get_default_mixer());
    al_set_audio_stream_playing(song.get(), false);

    music[filename] = song;
    return song;
}
*/

void Resources::Unload()
{
    bitmaps.clear();
    /*fonts.clear();
    sounds.clear();
    music.clear();*/
}

}