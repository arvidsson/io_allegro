#include "Window.hpp"
#include "Debug.hpp"
#include "render/Color.hpp"
#include "render/Camera.hpp"
#include "render/TileMap.hpp"
#include "resource/Image.hpp"
#include "resource/Font.hpp"
#include <sstream>
#include <cstdarg>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

namespace io
{

Window::Window(int width, int height, bool fullscreen, bool vsync, int multisampling)
{
    if (!al_init_primitives_addon()) {
        Throw("Failed to initialize primitives addon");
    }

    if (!al_init_image_addon()) {
        Throw("Failed to initialize image addon");
    }

    if (!al_init_font_addon()) {
        Throw("Failed to initialize font addon");
    }

    if (!al_init_ttf_addon()) {
        Throw("Failed to initialize ttf addon");
    }
    
    fullscreen ? al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW) : al_set_new_display_flags(ALLEGRO_WINDOWED);
    vsync ? al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE) : al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);
    if (multisampling) {
        al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
        al_set_new_display_option(ALLEGRO_SAMPLES, multisampling, ALLEGRO_REQUIRE);
    }
    
    display = std::shared_ptr<ALLEGRO_DISPLAY>(al_create_display(width, height), al_destroy_display);
    if (!display) {
        Throw("Failed to create %s display (%d x %d)", fullscreen ? "fullscreen" : "windowed", width, height);
    }
    al_set_window_title(display.get(), "io");
    camera = std::make_unique<Camera>();
    open = true;
}

void Window::SetTitle(const std::string &title)
{
    al_set_window_title(display.get(), title.c_str());
}

int Window::GetWidth() const
{
    return al_get_display_width(display.get());
}

int Window::GetHeight() const
{
    return al_get_display_height(display.get());
}

void Window::ToggleFullscreen()
{
    al_set_display_flag(display.get(), ALLEGRO_FULLSCREEN_WINDOW, !(al_get_display_flags(display.get()) & ALLEGRO_FULLSCREEN_WINDOW));
}

void Window::Render(Image image, const Vector<float> &position, int flip)
{
    al_draw_bitmap(image.get(), position.x, position.y, flip);
}

void Window::RenderTinted(Image image, const Color& tintColor, const Vector<float> &position, int flip)
{
    al_draw_tinted_bitmap(image.get(), tintColor.ToAllegroColor(), position.x, position.y, flip);
}

void Window::RenderRotated(Image image, const Vector<float> &center, const Vector<float> &position, float angle, int flip)
{
    al_draw_rotated_bitmap(image.get(), center.x, center.y, position.x, position.y, angle, flip);
}

void Window::RenderScaled(Image image, const Vector<float> &scale, const Vector<float> &position, int flip)
{
    al_draw_scaled_bitmap(image.get(), 0.0f, 0.0f, image.GetWidth(), image.GetHeight(), position.x, position.y, image.GetWidth() * scale.x, image.GetHeight() * scale.y, flip);
}

void Window::Print(Font font, const std::string &text, const Vector<float> &position, const Color &color, int alignment)
{
    al_draw_text(font.get(), color.ToAllegroColor(), position.x, position.y, alignment, text.c_str());
}

void Window::Printf(Font font, const Vector<float> &position, const Color &color, const char *format, ...)
{
    char buffer[4096];
    va_list ap;
    va_start(ap, format);
    vsprintf_s(buffer, format, ap);
    va_end(ap);

    Print(font, buffer, position, color);
}

void Window::Render(Tilemap &tilemap)
{
    auto cameraSize = camera->ToWorld(GetWidth(), GetHeight());
    auto cameraPos = Vector<float>(camera->GetX() - cameraSize.x / 2, camera->GetY() - cameraSize.y / 2);

    // figure out what tiles to draw depending on camera movement, so we don't waste time trying to draw every tile, visible or not
    Vector<int> topLeft = { (int)cameraPos.x / tilemap.GetTileWidth(), (int)cameraPos.y / tilemap.GetTileHeight() };
    if (topLeft.x < 0) topLeft.x = 0;
    if (topLeft.y < 0) topLeft.y = 0;
    Vector<int> bottomRight = { (int)(cameraSize.x) / tilemap.GetTileWidth() + 1, (int)(cameraSize.y) / tilemap.GetTileHeight() + 1 };
    if (bottomRight.x > tilemap.GetWidth()) bottomRight.x = tilemap.GetWidth();
    if (bottomRight.y > tilemap.GetHeight()) bottomRight.y = tilemap.GetHeight();

    al_hold_bitmap_drawing(true);
    for (int i = topLeft.x; i < bottomRight.x; i++) {
        for (int j = topLeft.y; j < bottomRight.y; j++) {
            float x = i * tilemap.GetTileWidth();
            float y = j * tilemap.GetTileHeight();
            auto tile = tilemap.GetTile(i, j);
            Render(tilemap.GetImageById(tile->GetID()), { x, y });
        }
    }
    al_hold_bitmap_drawing(false);
}

Camera& Window::GetCamera()
{
    Assert(camera != nullptr);
    return *camera.get();
}

void Window::HandleEvent(const ALLEGRO_EVENT &event)
{
    switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            Close();
            break;
    }
}

void Window::Clear()
{
    al_set_target_backbuffer(display.get());
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Window::Flip()
{
    al_flip_display();
}

}