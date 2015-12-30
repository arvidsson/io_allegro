#pragma once

#include "Pressable.hpp"
#include <vector>

namespace io
{

class Mouse
{
public:
    /*
        Initializes mouse input.
    */
    Mouse();

    /*
        Shows/hides mouse pointer.
    */
    void Show();
    void Hide();

    /*
        Mouse button codes.
    */
    enum Button
    {
        Left,
        Right,
        Middle,
        Max
    };

    /*
        Mouse input getters.
    */
    bool IsButtonDown(int button) const;
    bool IsButtonPressed(int button) const;
    bool IsButtonReleased(int button) const;
    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetZ() const { return z; }
    int GetDeltaX() const { return x - oldX; }
    int GetDeltaY() const { return y - oldY; }
    int GetDeltaZ() const { return z - oldZ; }

private:
    /*
        Clears keyboard input state, should be done each frame.
    */
    void Clear();

    /*
        Mouse input setters.
    */
    void ButtonWasPressed(int button);
    void ButtonWasReleased(int button);
    void WasMoved(int x, int y, int z);
    
    std::vector<Pressable> buttons;
    int x = 0, y = 0, z = 0;
    int oldX = 0, oldY = 0, oldZ = 0;
    
    friend class Input;
};

}