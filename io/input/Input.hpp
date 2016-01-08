#pragma once

#include "Keyboard.hpp"
#include "Mouse.hpp"
#include <alcpp.hpp>
#include <memory>

namespace io
{

class Input : public std::shared_ptr<Input>
{
public:
    Input() {}
    void Clear();

    Keyboard keyboard;
    Mouse mouse;

    // TODO: add joystick support
    // TODO: add touch input support
};

}