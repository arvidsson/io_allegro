#pragma once

#include <functional>

namespace io
{

class Harness
{
public:
    /*
        Helper function to catch and log exceptions when calling fn().
    */
    static void Main(std::function<void()> fn);
};

}