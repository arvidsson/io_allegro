#include "Config.hpp"
#include <cereal/archives/json.hpp>
#include <allegro5/allegro.h>
#include <fstream>

namespace io
{

Config::Config(int width, int height, bool fullscreen, bool vsync, int multisampling) :
    width(width), height(height), fullscreen(fullscreen), vsync(vsync), multisampling(multisampling) {}

bool Config::Exists(std::string path)
{
    return al_filename_exists(path.c_str());
}

void Config::Save(std::string path)
{
    std::ofstream file(path);
    cereal::JSONOutputArchive archive(file);
    archive(
        cereal::make_nvp("width", width),
        cereal::make_nvp("height", height),
        cereal::make_nvp("fullscreen", fullscreen),
        cereal::make_nvp("vsync", vsync),
        cereal::make_nvp("multisampling", multisampling)
    );
}

void Config::Load(std::string path)
{
    if (Exists(path)) {
        std::ifstream file(path);
        cereal::JSONInputArchive archive(file);
        archive(
            cereal::make_nvp("width", width),
            cereal::make_nvp("height", height),
            cereal::make_nvp("fullscreen", fullscreen),
            cereal::make_nvp("vsync", vsync),
            cereal::make_nvp("multisampling", multisampling)
        );
    }
}

}