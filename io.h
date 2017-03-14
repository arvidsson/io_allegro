/*
 * TODO
 * - game loop
 * - input
 * - math and math helpers (vector class)
 */

#ifndef IO_HEADER
#define IO_HEADER

#include <allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <vector>
#include <string>
#include <memory>

namespace io
{

/*
 * ==============================================================
 *
 *                          TYPES
 *
 * ===============================================================
 */
 
using Bitmap = std::shared_ptr<ALLEGRO_BITMAP>;
    
/*
 * ==============================================================
 *
 *                          API
 *
 * ===============================================================
 */

void init();
    
class Game
{
public:
    Game(std::string title, int width, int height, bool fullscreen);
    virtual ~Game();
    void run();
    void quit();
    virtual void update() = 0;
    virtual void render() = 0;
private:
    bool done = false;
    ALLEGRO_EVENT_QUEUE *queue = nullptr;
    ALLEGRO_TIMER *timer = nullptr;
    ALLEGRO_DISPLAY *display = nullptr;
};
    
Bitmap make_bitmap(int width, int height);
Bitmap load_bitmap(const std::string& filename);

}

/*
 * ==============================================================
 *
 *                        IMPLEMENTATION
 *
 * ===============================================================
 */

#ifdef IO_IMPLEMENTATION

namespace io
{

void init()
{
    al_init();
    
    ALLEGRO_PATH* resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
    al_destroy_path(resource_path);
    
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(32);
}

Game::Game(string title, int width, int height, bool fullscreen)
{
    queue = al_create_event_queue();

    timer = al_create_timer(1.0 / 60);
    
    fullscreen ? al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW) : al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(width, height);
    if (!display) {
        Throw("Failed to create %s display (%d x %d)", fullscreen ? "fullscreen" : "windowed", width, height);
    }
    al_set_window_title(display, title.c_str());

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
}
    
Game::~Game()
{
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_queue(queue);
}
    
void Game::run()
{
    
}
    
Bitmap make_bitmap(int width, int height)
{
    return Bitmap(al_create_bitmap(width, height), al_destroy_bitmap);
}
    
Bitmap load_bitmap(const std::string& filename)
{
    return Bitmap(al_load_bitmap(filename.c_str()), al_destroy_bitmap);   
}

}

#endif // IO_IMPLEMENTATION

#endif // IO_HEADER
