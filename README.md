# io

Allegro 5 C++ rapid game prototyping framework in a single header-file.

* Define `IO_IMPLEMENTATION` in *one* .cpp file before including `io.h`.
* Derive from `io::Game`.
* Use `IO()` macro to run the game.
* Use `io()` macro to access global game stuff (e.g. input).

```cpp
#define IO_IMPLEMENTATION
#include "io.h"

class Example : public io::Game
{
public:
    Example() : io::Game("Example", 800, 600, false) {}

    void update() override
    {
        if (io().input.is_key_down(ALLEGRO_KEY_ESCAPE))
        {
            quit();
        }
    }
    
    void render() override
    {
        // ...
    }
};

IO(Example);
```
