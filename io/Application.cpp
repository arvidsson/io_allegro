#include "Application.hpp"

using namespace alcpp;

namespace io
{

Core::Core()
{
    System::Init();
}

Application::Application()
{
    eventQueue.Register(alcpp::Keyboard::GetEventSource());
    done = false;
}

Application::Application(int width, int height, bool fullscreen) : Application()
{
    Initialize(width, height, fullscreen);
}

void Application::Initialize(int width, int height, bool fullscreen)
{
    display = Display(width, height, fullscreen);
    eventQueue.Register(display.GetEventSource());
}

void Application::Run()
{
    time.Start();

    while (!done) {
        time.Update();

        while (time.Step()) {
            Event event;

            do {
                event = eventQueue.GetNextEvent();

                switch (event.GetType()) {
                    case Event::Type::Timer:
                        TimerEvent();
                        break;

                    case Event::Type::KeyDown:
                        KeyPressEvent(event.GetKeyboardKeycode());
                        input.keyboard.KeyWasPressed(event.GetKeyboardKeycode());
                        break;

                    case Event::Type::KeyUp:
                        KeyReleaseEvent(event.GetKeyboardKeycode());
                        input.keyboard.KeyWasReleased(event.GetKeyboardKeycode());
                        break;

                    case Event::Type::MouseButtonDown:
                        MouseButtonPressEvent(event.GetMouseButton());
                        input.mouse.ButtonWasPressed(event.GetMouseButton());
                        break;

                    case Event::Type::MouseButtonUp:
                        MouseButtonReleaseEvent(event.GetMouseButton());
                        input.mouse.ButtonWasReleased(event.GetMouseButton());
                        break;

                    case Event::Type::MouseAxes:
                        MouseMoveEvent(event.GetMouseX(), event.GetMouseY());
                        MouseWheelEvent(event.GetMouseZ(), event.GetMouseW());
                        input.mouse.WasMoved(event.GetMouseX(), event.GetMouseY(), event.GetMouseZ(), event.GetMouseW());
                        break;

                    case Event::Type::DisplayClose:
                        Quit();
                        break;
                }
            } while (event);

            Update();
            input.Clear();
        }

        display.SetAsTarget();
        display.Clear({ 0, 0, 0 });
        Render();
        display.Flip();
    }
}

void Application::Quit()
{
    done = true;
}

}