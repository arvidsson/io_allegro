#include "Screens.hpp"
#include "../Debug.hpp"

namespace io
{

Screen& Screens::GetCurrent()
{
    Assert(!IsEmpty());
    return *screens.back();
}

void Screens::Push(Screen::Ptr screen)
{
    if (!IsEmpty()) {
        screens.back()->Terminate();
    }

    screens.push_back(screen);
    screens.back()->Initialize();
}

void Screens::Push(Screen *screen)
{
    Push(std::shared_ptr<Screen>(screen));
}

void Screens::Pop()
{
    if (!IsEmpty()) {
        screens.back()->Terminate();
        screens.pop_back();

        if (!IsEmpty()) {
            screens.back()->Initialize();
        }
    }
}

}