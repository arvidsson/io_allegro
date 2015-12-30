#pragma once

#include "math/Vector.hpp"
#include "math/Size.hpp"
#include "math/Rect.hpp"
#include <allegro5/allegro.h>
#include <string>
#include <memory>

namespace io
{

class Color;
class Camera;
class Image;
class Font;
class Tilemap;

class Window
{
public:
    /*
        Initializes the window.
    */
    Window(int width, int height, bool fullscreen, bool vsync = true, int multisampling = 0);
    
    /*
        Sets the window title.
    */
    void SetTitle(const std::string &title);

    /*
        Returns the window's dimensions.
    */
    int GetWidth() const;
    int GetHeight() const;

    /*
        Window open state.
    */
    bool IsOpen() const { return open; }
    void Close() { open = false; }

    /*
        Toggles between windowed and fullscreen mode.
    */
    void ToggleFullscreen();

    /*
        Renders images.
    */
    void Render(Image image, const Vector<float> &position, int flip = 0);
    void RenderTinted(Image image, const Color& tintColor, const Vector<float> &position, int flip = 0);
    void RenderRotated(Image image, const Vector<float> &center, const Vector<float> &position, float angle, int flip = 0);
    void RenderScaled(Image image, const Vector<float> &scale, const Vector<float> &position, int flip = 0);

    /*
        Renders text.
    */
    void Print(Font font, const std::string &text, const Vector<float> &position, const Color &color, int alignment = 0);
    void Printf(Font font, const Vector<float> &position, const Color &color, const char *format, ...);

    /*
        Renders tilemap
    */
    void Render(Tilemap &tilemap);

    /*
        Returns the main camera.
    */
    Camera& GetCamera();
    
private:
    /*
        Updates window state.
    */
    void HandleEvent(const ALLEGRO_EVENT &event);

    /*
        Clears the backbuffer.
    */
    void Clear();

    /*
        Flips the backbuffer.
    */
    void Flip();

    bool open = false;
    std::shared_ptr<ALLEGRO_DISPLAY> display = nullptr;
    std::shared_ptr<Camera> camera = nullptr;
    
    friend class Game;
};

}