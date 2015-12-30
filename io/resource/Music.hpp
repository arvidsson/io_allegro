#pragma once

#include "../util/SharedPtr.hpp"
#include <allegro5/allegro_audio.h>
#include <string>

namespace io
{
    
class Music : public SharedPtr<ALLEGRO_AUDIO_STREAM>
{
public:
    Music() {}
    Music(std::string filename) : SharedPtr(al_load_audio_stream(filename.c_str(), 4, 2048), al_destroy_audio_stream) {}
};
    
}