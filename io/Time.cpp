#include "Time.hpp"
#include <alcpp.hpp>
using namespace alcpp;

namespace io
{

Time::Time(double delta, double maxFrameTime)
{
    Initialize(delta, maxFrameTime);
}

void Time::Initialize(double delta, double maxFrameTime)
{
    this->delta = delta;
    this->maxFrameTime = maxFrameTime;
}

void Time::Start()
{
    currentTime = 0.0;
    accumulator = 0.0;
}

void Time::Update()
{
    double newTime = alcpp::Time::GetTime();
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

    alpha = accumulator / delta;
    return false;
}

double Time::GetDelta() const
{
    return delta;
}

double Time::GetAlpha() const
{
    return alpha;
}

}