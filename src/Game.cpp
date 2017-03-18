#include "Game.h"

namespace io
{

/*BEGIN*/

Game::Game(std::string title, Size2i window_size, bool fullscreen)
{
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);
    fullscreen ? al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW) : al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(window_size.w, window_size.h);
    al_set_window_title(display, title.c_str());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    io().window_size = window_size;
}
    
Game::~Game()
{
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}
    
void Game::run()
{
    bool redraw = true;
    al_start_timer(timer);
    auto& input = io().input;
    
    while (!done)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        
        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                if (!paused)
                {
                    update();
                }
                
                // clear input state
                for (auto& key : input.keyboard.keys)
                {
                    key.pressed = false;
                    key.released = false;
                }
                for (auto& button : input.mouse.buttons)
                {
                    button.pressed = false;
                    button.released = false;
                }
                input.mouse.old_x = input.mouse.x;
                input.mouse.old_y = input.mouse.y;
                input.mouse.old_z = input.mouse.z;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                input.keyboard.keys[event.keyboard.keycode].down = true;
                input.keyboard.keys[event.keyboard.keycode].pressed = true;
                break;

            case ALLEGRO_EVENT_KEY_UP:
                input.keyboard.keys[event.keyboard.keycode].down = false;
                input.keyboard.keys[event.keyboard.keycode].released = true;
                break;

            case ALLEGRO_EVENT_KEY_CHAR:
                if ((event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT) && event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                {
                    al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, !(al_get_display_flags(display) & ALLEGRO_FULLSCREEN_WINDOW));
                }
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                input.mouse.x = event.mouse.x;
                input.mouse.y = event.mouse.y;
                input.mouse.z = event.mouse.z;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                input.mouse.buttons[event.mouse.button - 1].down = true;
                input.mouse.buttons[event.mouse.button - 1].pressed = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                input.mouse.buttons[event.mouse.button - 1].down = false;
                input.mouse.buttons[event.mouse.button - 1].released = true;
                break;
                
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
                paused = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
                paused = false;
                break;
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            redraw = false;
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(0, 0, 0));
            render();
            al_flip_display();
        }
    }
}

/*END*/

} // namespace io