#pragma once

#include <alcpp.hpp>
#include <unordered_map>
#include <string>

namespace io
{

class Resources
{
public:
    // Retrieves resources (loads them from file if not found).
    alcpp::Bitmap GetBitmap(const std::string &filename);
    /*Font GetFont(const std::string &filename, int size);
    Sound GetSound(const std::string &filename);
    Music GetMusic(const std::string &filename);*/

    // Manually unload all resources.
    void Unload();

private:
    std::unordered_map<std::string, alcpp::Bitmap> bitmaps;
    /*std::unordered_map<std::string, Font> fonts;
    std::unordered_map<std::string, Sound> sounds;
    std::unordered_map<std::string, Music> music;*/
};

}