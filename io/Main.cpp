#include "Main.hpp"
#include "Debug.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

namespace io
{

void Main(std::function<void()> fn)
{
    try {
        fn();
    }
    catch (const std::exception &e) {
        LOG(ERROR) << "Exception: " << e.what();
        al_show_native_message_box(al_get_current_display(), "Error", "Exception!", e.what(), 0, ALLEGRO_MESSAGEBOX_ERROR);
    }
}

}