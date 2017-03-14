# io

Allegro 5 C++ rapid game prototyping framework in a single header-file.

## Usage

Define `IO_IMPLEMENTATION` in *one* .cpp file before including `io.h`.

```cpp
#define IO_IMPLEMENTATION
#include "io.h"

class Skeleton : public io::Game
{
public:
    void update(const io::Input& input) override
    {
        if (input.is_key_down(ALLEGRO_KEY_ESCAPE))
        {
            quit();
        }
    }
    
    void render() override
    {
        // ...
    }
};

IO_MAIN
{
    io::init();
    auto game = std::make_unique<Skeleton>();
    game->run();
}
IO_END
```

## License
 
The MIT License (MIT)

Copyright (c) 2017 Pär Arvidsson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
