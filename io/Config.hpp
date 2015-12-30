#pragma once

#include <string>

namespace io
{

struct Config
{
    Config(int width = 800, int height = 600, bool fullscreen = false, bool vsync = true, int multisampling = 0);

    bool Exists(std::string path);
    void Save(std::string path);
    void Load(std::string path);
    
    template <class Archive>
    void serialize(Archive &ar)
    {
        ar(width, height, fullscreen, vsync, multisampling);
    }

    int width, height;
    bool fullscreen;
    bool vsync;
    int multisampling;
};

}
