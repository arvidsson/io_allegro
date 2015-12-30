#include "Input.hpp"
#include "Debug.hpp"
#include "input/Keyboard.hpp"
#include "input/Mouse.hpp"

namespace io
{

Input::Input()
{
    keyboard = std::make_shared<Keyboard>();
    mouse = std::make_shared<Mouse>();
}

const Keyboard& Input::GetKeyboard() const
{
    Assert(keyboard != nullptr);
    return *keyboard.get();
}

const Mouse& Input::GetMouse() const
{
    Assert(mouse != nullptr);
    return *mouse.get();
}

void Input::HandleEvent(const ALLEGRO_EVENT &event)
{
    switch (event.type) {
        case ALLEGRO_EVENT_KEY_DOWN:
            keyboard->KeyWasPressed(event.keyboard.keycode);
            break;

        case ALLEGRO_EVENT_KEY_UP:
            keyboard->KeyWasReleased(event.keyboard.keycode);
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            mouse->ButtonWasPressed(event.mouse.button - 1);
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            mouse->ButtonWasReleased(event.mouse.button - 1);
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
            mouse->WasMoved(event.mouse.x, event.mouse.y, event.mouse.z);
            break;
    }
}   

void Input::Clear()
{
    keyboard->Clear();
    mouse->Clear();
}

}