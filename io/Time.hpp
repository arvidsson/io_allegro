#pragma once

namespace io
{

class Time
{
public:
    Time(double delta = 1.0 / 60.0, double maxFrameTime = 0.25);
    void Initialize(double delta, double maxFrameTime);

    void Start();
    void Update();
    bool Step();
    
    double GetDelta() const;
    double GetAlpha() const;

private:
    double currentTime = 0.0;
    double accumulator = 0.0;
    double maxFrameTime;
    double delta;
    double alpha = 0.0;
};

}