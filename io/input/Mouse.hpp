#pragma once

#include "Pressable.hpp"
#include <vector>
#include <memory>

namespace io
{

class Mouse : public std::shared_ptr<Mouse>
{
public:
    Mouse();
    void Clear();

    void ButtonWasPressed(int button);
    void ButtonWasReleased(int button);
    void WasMoved(int x, int y, int z, int w);

    bool IsButtonDown(int button) const;
    bool IsButtonPressed(int button) const;
    bool IsButtonReleased(int button) const;

    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetZ() const { return z; }
    int GetW() const { return w; }

    int GetDeltaX() const { return x - oldX; }
    int GetDeltaY() const { return y - oldY; }
    int GetDeltaZ() const { return z - oldZ; }
    int GetDeltaW() const { return w - oldW; }

private:
    std::vector<Pressable> buttons;
    int x = 0, y = 0, z = 0, w = 0;
    int oldX = 0, oldY = 0, oldZ = 0, oldW = 0;
};

}