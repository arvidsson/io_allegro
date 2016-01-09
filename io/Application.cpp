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
                    case Event::Type::KeyDown:
                        KeyPressEvent(event.GetKeyboardKeycode());
                        input.keyboard.KeyWasPressed(event.GetKeyboardKeycode());
                        break;

                    case Event::Type::KeyUp:
                        KeyReleaseEvent(event.GetKeyboardKeycode());
                        input.keyboard.KeyWasReleased(event.GetKeyboardKeycode());
                        break;

                    case Event::Type::KeyChar:
                        KeyCharEvent(event.GetKeyboardKeycode(), event.GetKeyboardCharacter(), event.GetKeyboardModifiers(), event.GetKeyboardRepeat());
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

                    case Event::Type::MouseWarped:
                        MouseWarpedEvent(event.GetMouseX(), event.GetMouseY());
                        input.mouse.WasMoved(event.GetMouseX(), event.GetMouseY(), event.GetMouseZ(), event.GetMouseW());
                        break;

                    case Event::Type::MouseEnterDisplay:
                        MouseEnterDisplay();
                        break;

                    case Event::Type::MouseLeaveDisplay:
                        MouseLeaveDisplay();
                        break;

                    case Event::Type::JoystickAxis:
                        JoystickAxisEvent(event.GetJoystickStick(), event.GetJoystickAxis(), event.GetJoystickAxisPosition());
                        break;

                    case Event::Type::JoystickButtonDown:
                        JoystickButtonPressEvent(event.GetJoystickButton());
                        break;

                    case Event::Type::JoystickButtonUp:
                        JoystickButtonReleaseEvent(event.GetJoystickButton());
                        break;

                    case Event::Type::JoystickConfiguration:
                        al_reconfigure_joysticks();
                        JoystickConfigurationEvent();
                        // TODO: update Input joystick handling
                        break;

                    case Event::Type::TouchBegin:
                        TouchBeginEvent(event.GetTouchId(), event.GetTouchX(), event.GetTouchY(), event.GetTouchPrimary());
                        break;

                    case Event::Type::TouchEnd:
                        TouchEndEvent(event.GetTouchId(), event.GetTouchX(), event.GetTouchY(), event.GetTouchPrimary());
                        break;

                    case Event::Type::TouchMove:
                        TouchMoveEvent(event.GetTouchId(), event.GetTouchX(), event.GetTouchY(), event.GetTouchPrimary());
                        break;

                    case Event::Type::TouchCancel:
                        TouchCancelEvent(event.GetTouchId(), event.GetTouchX(), event.GetTouchY(), event.GetTouchPrimary());
                        break;

                    case Event::Type::Timer:
                        TimerEvent();
                        break;

                    case Event::Type::DisplayExpose:
                        DisplayExposeEvent(event.GetDisplayX(), event.GetDisplayY(), event.GetDisplayWidth(), event.GetDisplayHeight());
                            break;

                    case Event::Type::DisplayResize:
                        DisplayResizeEvent(event.GetDisplayX(), event.GetDisplayY(), event.GetDisplayWidth(), event.GetDisplayHeight());
                        break;

                    case Event::Type::DisplayClose:
                        DisplayCloseEvent();
                        break;

                    case Event::Type::DisplayLost:
                        DisplayLostEvent();
                        break;

                    case Event::Type::DisplayFound:
                        DisplayFoundEvent();
                        break;

                    case Event::Type::DisplaySwitchOut:
                        DisplaySwitchOutEvent();
                        break;

                    case Event::Type::DisplaySwitchIn:
                        DisplaySwitchInEvent();
                        break;

                    case Event::Type::DisplayOrientation:
                        DisplayOrientationEvent(event.GetDisplayOrientation());
                        break;

                    case Event::Type::DisplayHaltDrawing:
                        DisplayHaltDrawingEvent();
                        break;

                    case Event::Type::DisplayResumeDrawing:
                        DisplayResumeDrawingEvent();
                        break;

                    case Event::Type::DisplayConnected:
                        DisplayConnectedEvent();
                        break;

                    case Event::Type::DisplayDisconnected:
                        DisplayDisconnectedEvent();
                        break;
                }
            } while (event);

            Update();
            input.Clear();
        }

        display.SetAsTarget();
        display.Clear(clearColor);
        Render();
        display.Flip();
    }
}

void Application::Quit()
{
    done = true;
}

}