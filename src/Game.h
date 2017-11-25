#pragma once

#include "Core.h"
#include "Size.h"
#include "Config.h"
#include "GameServices.h"

namespace io
{

/*BEGIN*/

class Game
{
public:
    Game(std::string title, Size2i window_size, bool fullscreen);
    Game(std::string title, std::string config_path);
    virtual ~Game();
    void run();
    void quit();
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void process_event(ALLEGRO_EVENT event) {}
protected:
    void initialize(std::string title, Size2i window_size, bool fullscreen);
    bool done = false;
    bool paused = false;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_DISPLAY* display;
};

/*END*/

} // namespace io