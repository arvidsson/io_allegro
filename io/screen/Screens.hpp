#pragma once

#include "Screen.hpp"
#include <vector>
#include <memory>

namespace io
{

class Screens
{
public:
    void Clear() { screens.clear(); }
    bool IsEmpty() const { return screens.empty(); }
    Screen& GetCurrent();

    void Push(Screen::Ptr screen);
    void Push(Screen *screen);
    void Pop();

private:
    std::vector<Screen::Ptr> screens;
};

}