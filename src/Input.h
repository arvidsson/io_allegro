#pragma once

#include "Core.h"

namespace io
{

/*BEGIN*/

class Input
{
public:
    bool is_key_down(int key) const { return keyboard.keys[key].down; }
    bool is_key_pressed(int key) const { return keyboard.keys[key].pressed; }
    bool is_key_released(int key) const { return keyboard.keys[key].released; }
    
    bool is_mouse_button_down(int button) const { return mouse.buttons[button].down; }
    bool is_mouse_button_pressed(int button) const { return mouse.buttons[button].pressed; }
    bool is_mouse_button_released(int button) const { return mouse.buttons[button].released; }
    int get_mouse_x() const { return mouse.x; }
    int get_mouse_y() const { return mouse.y; }
    
    static int wait_for_keypress();
    static void wait_for_any();
    
private:
    struct Pressable
    {
        bool down = false;
        bool pressed = false;
        bool released = false;
    };
    
    struct Keyboard
    {
        std::array<Pressable, ALLEGRO_KEY_MAX> keys;
    } keyboard;
    
    struct Mouse
    {
        std::array<Pressable, 10> buttons;
        int x, y, z;
        int old_x, old_y, old_z;
    } mouse;
    
    friend class Game;
};

/*END*/

} // namespace io