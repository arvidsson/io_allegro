#include "Keyboard.hpp"
#include "../Debug.hpp"

namespace io
{

Keyboard::Keyboard()
{
    if (!al_install_keyboard()) {
        Throw("Failed to install keyboard");
    }
    
    keys.assign(Key::Max, Pressable());
}

bool Keyboard::IsKeyDown(int keycode) const
{
    Assert(keycode >= 0 && keycode < Key::Max);
    return keys[keycode].down;
}

bool Keyboard::IsKeyPressed(int keycode) const
{
    Assert(keycode >= 0 && keycode < Key::Max);
    return keys[keycode].pressed;
}

bool Keyboard::IsKeyReleased(int keycode) const
{
    Assert(keycode >= 0 && keycode < Key::Max);
    return keys[keycode].released;
}

int Keyboard::WaitForKeypress()
{
    auto queue = std::shared_ptr<ALLEGRO_EVENT_QUEUE>(al_create_event_queue(), al_destroy_event_queue);
    al_register_event_source(queue.get(), al_get_keyboard_event_source());
    ALLEGRO_EVENT event;
    do {
        al_wait_for_event(queue.get(), &event);
    } while (event.type != ALLEGRO_EVENT_KEY_DOWN);
    return event.keyboard.keycode;
}

void Keyboard::Clear()
{
    for (auto &key : keys) {
        key.pressed = false;
        key.released = false;
    }
}

void Keyboard::KeyWasPressed(int keycode)
{
    keys[keycode].down = true;
    keys[keycode].pressed = true;
}

void Keyboard::KeyWasReleased(int keycode)
{
    keys[keycode].down = false;
    keys[keycode].released = true;
}

}