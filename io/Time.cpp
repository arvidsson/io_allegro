#include "Time.hpp"
#include <allegro5/allegro.h>

namespace io
{

double Time::GetDelta() const
{
    return delta;
}

double Time::GetAlpha() const
{
    return accumulator / delta;
}

void Time::Start()
{
    currentTime = 0.0;
    accumulator = 0.0;
}

void Time::Update()
{
    double newTime = al_get_time();
    double frameTime = newTime - currentTime;
    if (frameTime > maxFrameTime) {
        frameTime = 0.25;
    }
    currentTime = newTime;
    accumulator += frameTime;
}

bool Time::Step()
{
    if (accumulator >= delta) {
        accumulator -= delta;
        return true;
    }
    
    return false;
}

}