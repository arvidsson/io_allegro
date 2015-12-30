#pragma once

#include <vector>

namespace io
{

class PerlinNoise
{
public:
    // Initialize with the reference values for the permutation vector
    PerlinNoise();

    // Generate a new permutation vector based on the value of seed
    PerlinNoise(unsigned int seed);

    // Get a noise value, for 2D images z can have any value
    double Noise(double x, double y, double z);

private:
    double Fade(double t);
    double Lerp(double t, double a, double b);
    double Grad(int hash, double x, double y, double z);

    // The permutation vector
    std::vector<int> p;
};

}