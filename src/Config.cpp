#include "Config.h"

namespace io
{

/*BEGIN*/

Config::Config(std::string filename)
{
    cfg = al_load_config_file(filename.c_str());
    if (!cfg)
    {
        IO_THROW("Failed to load config file: %s", cfg);
    }
}

Config::~Config()
{
    al_destroy_config(cfg);
}

bool Config::has_value(std::string key, std::string section)
{
    if (al_get_config_value(cfg, section.c_str(), key.c_str()))
    {
        return true;
    }
    return false;
}

bool Config::get_bool(std::string key, std::string section)
{
    std::string value = al_get_config_value(cfg, section.c_str(), key.c_str());
    if (value.compare("true") == 0)
    {
        return true;
    }
    return false;
}

int Config::get_int(std::string key, std::string section)
{
    std::string value = al_get_config_value(cfg, section.c_str(), key.c_str());
    return std::stoi(value);
}

float Config::get_float(std::string key, std::string section)
{
    std::string value = al_get_config_value(cfg, section.c_str(), key.c_str());
    return std::stof(value);
}

std::string Config::get_string(std::string key, std::string section)
{
    std::string value = al_get_config_value(cfg, section.c_str(), key.c_str());
    return value;
}


/*END*/

} // namespace io