#include "Mouse.hpp"
#include "../Debug.hpp"
#include <allegro5/allegro.h>

namespace io
{

Mouse::Mouse()
{
    if (!al_install_mouse()) {
        Throw("Failed to install mouse");
    }
    
    buttons.assign(Button::Max, Pressable());
}

void Mouse::Show()
{
    al_show_mouse_cursor(al_get_current_display());
}

void Mouse::Hide()
{
    al_hide_mouse_cursor(al_get_current_display());
}

bool Mouse::IsButtonDown(int button) const
{
    Assert(button >= 0 && button < Button::Max);
    return buttons[button].down;
}

bool Mouse::IsButtonPressed(int button) const
{
    Assert(button >= 0 && button < Button::Max);
    return buttons[button].pressed;
}

bool Mouse::IsButtonReleased(int button) const
{
    Assert(button >= 0 && button < Button::Max);
    return buttons[button].released;
}

void Mouse::Clear()
{
    for (auto &button : buttons) {
        button.pressed = false;
        button.released = false;
    }

    oldX = x;
    oldY = y;
    oldZ = z;
}

void Mouse::ButtonWasPressed(int button)
{
    buttons[button].down = true;
    buttons[button].pressed = true;
}

void Mouse::ButtonWasReleased(int button)
{
    buttons[button].down = false;
    buttons[button].released = true;
}

void Mouse::WasMoved(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

}