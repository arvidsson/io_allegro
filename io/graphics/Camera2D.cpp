#include "Camera2D.hpp"
using namespace alcpp;

namespace io
{

void Camera2D::Use()
{
    ApplyTransform(transform);
    transform.Use();
}

void Camera2D::Reset()
{
    transform.Identity();
    transform.Use();
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

Vector<float> Camera2D::ToScreen(float x, float y)
{
    Transform t;
    ApplyTransform(t);
    return t.TransformCoordinates(x, y);
}

Vector<float> Camera2D::ToScreen(const Vector<float> &coords)
{
    return ToScreen(coords.x, coords.y);
}

Vector<float> Camera2D::ToWorld(float x, float y)
{
    Transform t;
    ApplyTransform(t);
    t.Invert();
    return t.TransformCoordinates(x, y);
}

Vector<float> Camera2D::ToWorld(const Vector<float> &coords)
{
    return ToWorld(coords.x, coords.y);
}

void Camera2D::ApplyTransform(Transform &t)
{
    t.Identity();
    
    // move, rotate, zoom
    t.Translate(-x, -y);
    t.Rotate(rotate);
    t.Scale(zoom, zoom);

    // center camera
    auto width = al_get_display_width(al_get_current_display());
    auto height = al_get_display_height(al_get_current_display());
    t.Translate(width / 2, height / 2);
}

}