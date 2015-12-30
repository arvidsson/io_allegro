#pragma once

namespace io
{

// Stores the state of keys, buttons, etc...
struct Pressable
{
    bool down = false;
    bool pressed = false;
    bool released = false;
};

}