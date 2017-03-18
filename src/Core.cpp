#include "Core.h"
using namespace io;

/*BEGIN*/

void init()
{
    IO_CHECK(al_init(), "Failed to initialize allegro");
    IO_CHECK(al_install_keyboard(), "Failed to install keyboard");
    IO_CHECK(al_install_mouse(), "Failed to install mouse");
    
    ALLEGRO_PATH* resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
    al_destroy_path(resource_path);
    
    IO_CHECK(al_init_primitives_addon(), "Failed to initialize primitives addon");
    IO_CHECK(al_init_image_addon(), "Failed to initialize image addon");
    IO_CHECK(al_init_font_addon(), "Failed to initialize font addon");
    IO_CHECK(al_init_ttf_addon(), "Failed to initialize ttf addon");
    IO_CHECK(al_install_audio(), "Failed to install audio addon");
    IO_CHECK(al_init_acodec_addon(), "Failed to initialize acodec addon");
    IO_CHECK(al_reserve_samples(32), "Failed to reserve samples");
}

void throw_exception(const char *file, int line, const char *format, ...)
{
    char buffer[4096];
    va_list ap;
    va_start(ap, format);
    vsprintf_s(buffer, format, ap);
    va_end(ap);
    std::stringstream ss;
    ss << buffer << " (" << file << ":" << line << ")";
    throw std::runtime_error(ss.str());
}

/*END*/