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
    void use() { get_transform().use(); }
    void reset() { Transform t; t.use(); }
    void move_to(Vector2f new_pos) { pos = new_pos; }
    void move_by(Vector2f scroll) { pos -= scroll; }
    void zoom_to(float z) { this->z = z; }
    void zoom_by(float z) { this->z += z; }
    void rotate_to(float r) { this->r = r; }
    void rotate_by(float r) { this->r += r; }
    float x() const { return pos.x; }
    float y() const { return pos.y; }
    float zoom() const { return z; }
    float rotation() const { return r; }
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