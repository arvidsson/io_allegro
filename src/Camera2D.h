#pragma once

#include "Core.h"
#include "Vector.h"
#include "Transform.h"

namespace io
{

/*BEGIN*/

class Camera2D
{
public:
    void use();
    void reset();
    void move_to(Vector2f new_pos);
    void move_by(Vector2f scroll_factor);
    void zoom_to(float new_zoom);
    void zoom_by(float zoom_factor);
    void rotate_to(float new_rotation);
    void rotate_by(float rotation_factor);
    float x() const;
    float y() const;
    float zoom() const;
    float rotation() const;
    Vector2f to_screen(Vector2f coords) const;
    Vector2f to_world(Vector2f coords) const;
private:
    Transform get_transform() const;
    Vector2f pos;
    float z = 1.0;
    float r = 0.0f;
};

/*END*/

} // namespace io