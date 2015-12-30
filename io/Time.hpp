#pragma once

namespace io
{

class Time
{
public:
    Time(double delta = 1.0 / 60.0, double maxFrameTime = 0.25) : delta(delta), maxFrameTime(maxFrameTime) {}
    
    /*
        Returns the delta. Use this in logic update, e.g. when something moves.
    */
    double GetDelta() const;
    
    /*
        Returns the alpha. Use this to update render state, we need to know previous and current state in order to interpolate.
    */
    double GetAlpha() const;

private:
    /*
        Initializes time state.
    */
    void Start();
    
    /*
        Calculates frame time so that we know how many logic updates we need.
    */
    void Update();
    
    /*
        Returns true if we should update logic one more time.
    */
    bool Step();

    double currentTime = 0.0;
    double accumulator = 0.0;
    const double maxFrameTime;
    const double delta;
    
    friend class Game;
};

}