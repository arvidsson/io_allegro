#include "Camera.hpp"

namespace io
{

void Camera::Use()
{
    ApplyTransform(&transform);
    al_use_transform(&transform);
}

void Camera::Reset()
{
    al_identity_transform(&transform);
    al_use_transform(&transform);
}

void Camera::MoveTo(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Camera::MoveBy(float scrollX, float scrollY)
{
    x -= scrollX;
    y -= scrollY;
}

void Camera::ZoomTo(float z)
{
    zoom = z;
}

void Camera::ZoomBy(float z)
{
    zoom += z;
}

void Camera::RotateTo(float r)
{
    rotate = r;
}

void Camera::RotateBy(float r)
{
    rotate += r;
}

Vector<float> Camera::ToScreen(float x, float y)
{
    ALLEGRO_TRANSFORM t;
    ApplyTransform(&t);
    al_transform_coordinates(&t, &x, &y);
    return Vector<float>(x, y);
}

Vector<float> Camera::ToScreen(const Vector<float> &coords)
{
    return ToScreen(coords.x, coords.y);
}

Vector<float> Camera::ToWorld(float x, float y)
{
    ALLEGRO_TRANSFORM t;
    ApplyTransform(&t);
    al_invert_transform(&t);
    al_transform_coordinates(&t, &x, &y);
    return Vector<float>(x, y);
}

Vector<float> Camera::ToWorld(const Vector<float> &coords)
{
    return ToWorld(coords.x, coords.y);
}

void Camera::ApplyTransform(ALLEGRO_TRANSFORM *t)
{
    al_identity_transform(t);
    
    // move, rotate, zoom
    al_translate_transform(t, -x, -y);
    al_rotate_transform(t, rotate);
    al_scale_transform(t, zoom, zoom);

    // center camera
    auto width = al_get_display_width(al_get_current_display());
    auto height = al_get_display_height(al_get_current_display());
    al_translate_transform(t, width / 2, height / 2);
}

}