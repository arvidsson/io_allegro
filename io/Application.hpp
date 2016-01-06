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

    virtual void TimerEvent() {}
    virtual void KeyPressEvent(int key) {}
    virtual void KeyReleaseEvent(int key) {}
    virtual void MouseButtonPressEvent(int button) {}
    virtual void MouseButtonReleaseEvent(int button) {}
    virtual void MouseMoveEvent(int x, int y) {}
    virtual void MouseWheelEvent(int z, int w) {}

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
