#include "Camera2D.hpp"
using namespace alcpp;

namespace io
{

void Camera2D::Use()
{
    Transform t = GetTransform();
    t.Use();
}

void Camera2D::Reset()
{
    Transform t;
    t.Use();
}

void Camera2D::MoveTo(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Camera2D::MoveBy(float scrollX, float scrollY)
{
    x -= scrollX;
    y -= scrollY;
}

void Camera2D::ZoomTo(float z)
{
    zoom = z;
}

void Camera2D::ZoomBy(float z)
{
    zoom += z;
}

void Camera2D::RotateTo(float r)
{
    rotate = r;
}

void Camera2D::RotateBy(float r)
{
    rotate += r;
}

Vec2<float> Camera2D::ToScreen(float x, float y) const
{
    Transform t = GetTransform();
    return t.TransformCoordinates(x, y);
}

Vec2<float> Camera2D::ToScreen(const Vec2<float> &coords) const
{
    return ToScreen(coords.x, coords.y);
}

Vec2<float> Camera2D::ToWorld(float x, float y) const
{
    Transform t = GetTransform();
    t.Invert();
    return t.TransformCoordinates(x, y);
}

Vec2<float> Camera2D::ToWorld(const Vec2<float> &coords) const
{
    return ToWorld(coords.x, coords.y);
}

Transform Camera2D::GetTransform() const
{
    Transform t;
    
    // move, rotate, zoom
    t.Translate(-x, -y);
    t.Rotate(rotate);
    t.Scale(zoom, zoom);

    // center camera
    auto width = al_get_display_width(al_get_current_display());
    auto height = al_get_display_height(al_get_current_display());
    t.Translate(width / 2, height / 2);

    return t;
}

}