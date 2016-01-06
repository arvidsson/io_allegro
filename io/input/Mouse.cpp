#include "Mouse.hpp"
#include "../Debug.hpp"
#include <alcpp.hpp>
using namespace alcpp;

namespace io
{

Mouse::Mouse()
{
    buttons.assign(MouseButton::Max, Pressable());
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
    oldW = w;
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

void Mouse::WasMoved(int x, int y, int z, int w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

bool Mouse::IsButtonDown(int button) const
{
    Assert(button >= 0 && button < MouseButton::Max);
    return buttons[button].down;
}

bool Mouse::IsButtonPressed(int button) const
{
    Assert(button >= 0 && button < MouseButton::Max);
    return buttons[button].pressed;
}

bool Mouse::IsButtonReleased(int button) const
{
    Assert(button >= 0 && button < MouseButton::Max);
    return buttons[button].released;
}

}