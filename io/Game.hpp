#pragma once

#include <allegro5/allegro.h>
#include <memory>

namespace io
{

class Time;
class Input;
class Window;
class Audio;

class Game
{
public:
    Game();
    virtual ~Game() {}
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    void Run();
    
    virtual void Update() = 0;
    virtual void Render() = 0;

    Time& GetTime();
    Input& GetInput();
    Window& GetWindow();
    Audio& GetAudio();
    
protected:
    std::shared_ptr<Time> time = nullptr;
    std::shared_ptr<Input> input = nullptr;
    std::shared_ptr<Window> window = nullptr;
    std::shared_ptr<Audio> audio = nullptr;
};

}