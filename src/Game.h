#pragma once

#include "Core.h"
#include "Size.h"
#include "GameServices.h"

namespace io
{

/*BEGIN*/

class Game
{
public:
    Game(std::string title, Size2i window_size, bool fullscreen);
    virtual ~Game();
    void run();
    void quit() { done = true; }
    virtual void update() = 0;
    virtual void render() = 0;
private:
    bool done = false;
    bool paused = false;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_DISPLAY* display;
};

/*END*/

} // namespace io