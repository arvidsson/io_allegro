#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <random>
#include <vector>
#include <array>
#include <unordered_map>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <ctime>
#include <cstdarg>

namespace io
{

/*BEGIN*/

#define io() io::GameServices::instance()
#define IO(T) \
int main(int argc, char** argv) try\
{\
    io::init();\
    auto game = std::make_unique<T>();\
    game->run();\
}\
catch(const std::exception& e)\
{\
    al_show_native_message_box(al_get_current_display(), "Error", "Exception!", e.what(), 0, ALLEGRO_MESSAGEBOX_ERROR);\
}
#define IO_THROW(...) (io::throw_exception(__FILE__, __LINE__, __VA_ARGS__))
#define IO_CHECK(cond, msg) if (!cond) { IO_THROW(msg); }

void init();
void throw_exception(const char *file, int line, const char *format, ...);

/*END*/

} // namespace io