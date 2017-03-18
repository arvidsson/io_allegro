#pragma once

#include "Core.h"

namespace io
{

/*BEGIN*/

class Random
{
public:
    Random(unsigned int seed = (unsigned int)time(0));
    int get_next_int(int min, int max);
    float get_next_float(float min, float max);
    bool one_in(int chance);
    int roll_dice(int number, int sides);

private:
    std::mt19937 rng;
};

/*END*/

} // namespace io