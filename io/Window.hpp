#pragma once

#include "math/Vector.hpp"
#include "math/Size.hpp"
#include "math/Rect.hpp"
#include "graphics/Camera2D.hpp"
#include "graphics/TileMap.hpp"
#include "resource/Image.hpp"
#include "resource/Font.hpp"
#include <alcpp.hpp>
#include <string>
#include <memory>

namespace io
{

class Window
{
public:
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
        Toggles between windowed and fullscreen mode.
    */
    void ToggleFullscreen();

    /*
        Renders images.
    */
    void Render(Image image, const Vector<float> &position, int flip = 0);
    void RenderTinted(Image image, const alcpp::Color& tintColor, const Vector<float> &position, int flip = 0);
    void RenderRotated(Image image, const Vector<float> &center, const Vector<float> &position, float angle, int flip = 0);
    void RenderScaled(Image image, const Vector<float> &scale, const Vector<float> &position, int flip = 0);

    /*
        Renders text.
    */
    void Print(Font font, const std::string &text, const Vector<float> &position, const alcpp::Color &color, int alignment = 0);
    void Printf(Font font, const Vector<float> &position, const alcpp::Color &color, const char *format, ...);

    /*
        Renders tilemap
    */
    void Render(Tilemap &tilemap);
    
    Camera2D camera;
    
private:
    /*
        Clears the backbuffer.
    */
    void Clear();

    /*
        Flips the backbuffer.
    */
    void Flip();
    
    friend class Framework;
};

}