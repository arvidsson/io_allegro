#pragma once

#include "Time.hpp"
#include "input/Input.hpp"
#include "Resources.hpp"
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
    virtual ~Application();
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
    virtual void TouchBeginEvent(int id, int x, int y, bool primary) {}
    virtual void TouchEndEvent(int id, int x, int y, bool primary) {}
    virtual void TouchMoveEvent(int id, int x, int y, bool primary) {}
    virtual void TouchCancelEvent(int id, int x, int y, bool primary) {}
    virtual void TimerEvent() {}
    virtual void DisplayExposeEvent(int x, int y, int width, int height) {}
    virtual void DisplayResizeEvent(int x, int y, int width, int height) {}
    virtual void DisplayCloseEvent() { Quit(); }
    virtual void DisplayLostEvent() {}
    virtual void DisplayFoundEvent() {}
    virtual void DisplaySwitchOutEvent() {}
    virtual void DisplaySwitchInEvent() {}
    virtual void DisplayOrientationEvent(int orientation) {}
    virtual void DisplayHaltDrawingEvent() {}
    virtual void DisplayResumeDrawingEvent() {}
    virtual void DisplayConnectedEvent() {}
    virtual void DisplayDisconnectedEvent() {}

    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    alcpp::Display display;
    alcpp::Color clearColor = { 0, 0, 0 };
    Time time;
    Input input;
    Resources resources;

private:
    bool done = true;
    alcpp::EventQueue eventQueue;
};

}
