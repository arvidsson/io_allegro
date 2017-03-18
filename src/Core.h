#pragma once

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