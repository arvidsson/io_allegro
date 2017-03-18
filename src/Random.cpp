#include "Random.h"

namespace io
{

/*BEGIN*/

Random::Random(unsigned int seed)
{
    rng.seed(seed);
}

int Random::get_next_int(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

float Random::get_next_float(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

bool Random::one_in(int chance)
{
    if (get_next_int(0, chance - 1) == 0)
        return true;
    return false;
}

int Random::roll_dice(int number, int sides)
{
    int result = 0;
    for (int i = 0; i < number; i++)
        result += get_next_int(1, sides);
    return result;
}

/*END*/

} // namespace io