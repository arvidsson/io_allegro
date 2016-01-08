#pragma once

#include "Time.hpp"
#include "input/Input.hpp"
#include <alcpp.hpp>
#include <allegro5/allegro.h>

namespace io
{

class Core
{
public:
    Core();
};

class Application : public Core
{
public:
    Application();
    Application(int width, int height, bool fullscreen = false);
    void Initialize(int width, int height, bool fullscreen = false);
    void Run();
    void Quit();
    
    // events
    virtual void KeyPressEvent(int key) {}
    virtual void KeyReleaseEvent(int key) {}
    virtual void KeyCharEvent(int key, int unichar, int modifiers, bool repeat) {}
    virtual void MouseButtonPressEvent(int button) {}
    virtual void MouseButtonReleaseEvent(int button) {}
    virtual void MouseMoveEvent(int x, int y) {}
    virtual void MouseWheelEvent(int z, int w) {}
    virtual void MouseWarpedEvent(int x, int y) {}
    virtual void MouseEnterDisplay() {}
    virtual void MouseLeaveDisplay() {}
    virtual void JoystickAxisEvent(int stick, int axis, float pos) {}
    virtual void JoystickButtonPressEvent(int button) {}
    virtual void JoystickButtonReleaseEvent(int button) {}
    virtual void JoystickConfigurationEvent() {}
    virtual void TouchBeginEvent() {}
    virtual void TouchEndEvent() {}
    virtual void TouchMoveEvent() {}
    virtual void TouchCancelEvent() {}
    virtual void TimerEvent() {}
    virtual void DisplayCloseEvent() { Quit(); }
    // TODO: rest of display events

    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    alcpp::Display display;
    Time time;
    Input input;

private:
    bool done = true;
    alcpp::EventQueue eventQueue;
};

}
