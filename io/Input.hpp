#pragma once

#include <allegro5/allegro.h>
#include <memory>

namespace io
{

class Keyboard;
class Mouse;

class Input
{
public:
    Input();
    
    const Keyboard& GetKeyboard() const;
    const Mouse& GetMouse() const;

private:
    /*
        Updates input state.
    */
    void HandleEvent(const ALLEGRO_EVENT &event);

    /*
        Clears input state, should be done each frame.
    */
    void Clear();
    
    std::shared_ptr<Keyboard> keyboard = nullptr;
    std::shared_ptr<Mouse> mouse = nullptr;
    
    friend class Game;
};

}