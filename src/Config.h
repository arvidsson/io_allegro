#pragma once

#include "Core.h"

namespace io
{

/*BEGIN*/

class Config
{
public:
    Config(std::string filename);
    ~Config();
    bool has_value(std::string key, std::string section = "");
    bool get_bool(std::string key, std::string section = "");
    int get_int(std::string key, std::string section = "");
    float get_float(std::string key, std::string section = "");
    std::string get_string(std::string key, std::string section = "");

private:
    ALLEGRO_CONFIG* cfg;
};

/*END*/

} // namespace io