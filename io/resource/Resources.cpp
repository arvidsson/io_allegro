#include "Resources.hpp"
#include "../Debug.hpp"
#include "Image.hpp"
#include "Font.hpp"
#include "Sound.hpp"
#include "Music.hpp"

namespace io
{

Image Resources::GetImage(const std::string &filename)
{
    if (images.find(filename) != images.end()) {
        return images[filename];
    }

    Image image(filename);
    if (!image) {
        Throw("Failed to load image: %s", filename.c_str());
    }

    images[filename] = image;
    return image;
}

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

void Resources::Unload()
{
    images.clear();
    fonts.clear();
    sounds.clear();
    music.clear();
}

}