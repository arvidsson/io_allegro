#pragma once

#include "Size.h"
#include "Input.h"
#include "Random.h"

namespace io
{

/*BEGIN*/

class GameServices
{
public:
    static GameServices& instance() { static GameServices gs; return gs; }
    Size2i window_size;
    Input input;
    Random random;
};

/*END*/

} // namespace io