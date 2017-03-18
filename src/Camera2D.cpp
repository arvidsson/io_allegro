#include "Camera2D.h"

namespace io
{

/*BEGIN*/

void Camera2D::use()
{
    get_transform().use();
}

void Camera2D::reset()
{
    Transform t;
    t.use();
}

void Camera2D::move_to(Vector2f new_pos)
{
    pos = new_pos;
}

void Camera2D::move_by(Vector2f scroll_factor)
{
    pos -= scroll_factor;
}

void Camera2D::zoom_to(float new_zoom)
{
    z = new_zoom;
}

void Camera2D::zoom_by(float zoom_factor)
{
    z += zoom_factor;
}

void Camera2D::rotate_to(float new_rotation)
{
    r = new_rotation;
}

void Camera2D::rotate_by(float rotation_factor)
{
    r += rotation_factor;
}

float Camera2D::x() const
{
    return pos.x;
}

float Camera2D::y() const
{
    return pos.y;
}

float Camera2D::zoom() const
{
    return z;
}

float Camera2D::rotation() const
{
    return r;
}

Vector2f Camera2D::to_screen(Vector2f coords) const
{
    return get_transform().transform_coordinates(coords);
}

Vector2f Camera2D::to_world(Vector2f coords) const
{
    return get_transform().inverted().transform_coordinates(coords);
}

Transform Camera2D::get_transform() const
{
    Transform t;

    // move, rotate, zoom
    t.translate(-pos);
    t.rotate(r);
    t.scale({ z, z });

    // center camera
    auto width = al_get_display_width(al_get_current_display());
    auto height = al_get_display_height(al_get_current_display());
    t.translate({ width / 2.0f, height / 2.0f });

    return t;
}

/*END*/

} // namespace io