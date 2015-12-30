#pragma once

#include "../util/SharedPtr.hpp"
#include <allegro5/allegro_audio.h>
#include <string>

namespace io
{

class Sound : public SharedPtr<ALLEGRO_SAMPLE>
{
public:
    Sound() {}
    Sound(std::string filename) : SharedPtr(al_load_sample(filename.c_str()), al_destroy_sample) {}
};

}