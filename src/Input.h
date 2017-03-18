#pragma once

#include "Core.h"
#include "Vector.h"

namespace io
{

/*BEGIN*/

class Input
{
public:
    bool is_key_down(int key) const;
    bool is_key_pressed(int key) const;
    bool is_key_released(int key) const;

    bool is_mouse_button_down(int button) const;
    bool is_mouse_button_pressed(int button) const;
    bool is_mouse_button_released(int button) const;
    Vector2i get_mouse_pos() const;
    
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
        Vector2i pos;
        Vector2i old_pos;
        int wheel, old_wheel;
    } mouse;
    
    friend class Game;
};

/*END*/

} // namespace io