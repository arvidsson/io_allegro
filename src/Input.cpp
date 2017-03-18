#include "Input.h"

namespace io
{

/*BEGIN*/

bool Input::is_key_down(int key) const
{
    return keyboard.keys[key].down;
}

bool Input::is_key_pressed(int key) const
{
    return keyboard.keys[key].pressed;
}

bool Input::is_key_released(int key) const
{
    return keyboard.keys[key].released;
}

bool Input::is_mouse_button_down(int button) const
{
    return mouse.buttons[button].down;
}

bool Input::is_mouse_button_pressed(int button) const
{
    return mouse.buttons[button].pressed;
}

bool Input::is_mouse_button_released(int button) const
{
    return mouse.buttons[button].released;
}

Vector2i Input::get_mouse_pos() const
{
    return mouse.pos;
}

int Input::wait_for_keypress()
{
    auto queue = std::shared_ptr<ALLEGRO_EVENT_QUEUE>(al_create_event_queue(), al_destroy_event_queue);
    al_register_event_source(queue.get(), al_get_keyboard_event_source());
    ALLEGRO_EVENT event;
    do {
        al_wait_for_event(queue.get(), &event);
    } while (event.type != ALLEGRO_EVENT_KEY_DOWN);
    return event.keyboard.keycode;
}

void Input::wait_for_any()
{
    auto queue = std::shared_ptr<ALLEGRO_EVENT_QUEUE>(al_create_event_queue(), al_destroy_event_queue);
    al_register_event_source(queue.get(), al_get_keyboard_event_source());
    ALLEGRO_EVENT event;
    do {
        al_wait_for_event(queue.get(), &event);
    } while (event.type != ALLEGRO_EVENT_KEY_DOWN || event.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN);
}

/*END*/

} // namespace io