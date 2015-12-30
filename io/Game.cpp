#include "Game.hpp"
#include "Debug.hpp"
#include "Time.hpp"
#include "Input.hpp"
#include "Window.hpp"

namespace io
{

Game::Game()
{
    if (!al_init()) {
        Throw("Failed to initialize allegro");
    }
}

void Game::Run()
{
    Assert(time && input && window && audio);
    auto eventQueue = std::shared_ptr<ALLEGRO_EVENT_QUEUE>(al_create_event_queue(), al_destroy_event_queue);
    if (!eventQueue) {
        Throw("Failed to create event queue");
    }
    al_register_event_source(eventQueue.get(), al_get_keyboard_event_source());
    al_register_event_source(eventQueue.get(), al_get_mouse_event_source());
    al_register_event_source(eventQueue.get(), al_get_display_event_source(window->display.get()));
    time->Start();
    
    while (window->IsOpen()) {
        time->Update();

        while (time->Step()) {
            // input
            ALLEGRO_EVENT event;
            while (al_get_next_event(eventQueue.get(), &event)) {
                window->HandleEvent(event);
                input->HandleEvent(event);
            }

            // logic
            Update();
            input->Clear();
        }

        // render
        window->Clear();
        Render();
        window->Flip();
    }
}

Time& Game::GetTime()
{
    return *time;
}

Input& Game::GetInput()
{
    return *input;
}

Window& Game::GetWindow()
{
    return *window;
}

Audio& Game::GetAudio()
{
    return *audio;
}

}