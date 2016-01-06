#pragma once

#include "Pressable.hpp"
#include <vector>
#include <memory>

namespace io
{

class Keyboard : public std::shared_ptr<Keyboard>
{
public:
    Keyboard();
    void Clear();

    void KeyWasPressed(int keycode);
    void KeyWasReleased(int keycode);

    bool IsKeyDown(int keycode) const;
    bool IsKeyPressed(int keycode) const;
    bool IsKeyReleased(int keycode) const;

    int WaitForKeypress();

private:
    std::vector<Pressable> keys;
};

}