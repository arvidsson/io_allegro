#pragma once

#include <random>
#include <ctime>

namespace io
{

class Random
{
public:
    // Seeds the rng with the time.
    Random() { rng.seed((unsigned int)time(0)); }

    // Manually seeds the rng with a value.
    void Seed(unsigned int value) { rng.seed(value); }

    // Returns random integer.
    template <typename T>
    T GetNextInt(T max, T min = 0)
    {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(rng);
    }

    // Returns random real number.
    template <typename T>
    T GetNextReal(T max, T min = 0)
    {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(rng);
    }

private:
    std::mt19937 rng;
};

}