#pragma once

#include "Core.h"
#include "Vector.h"

namespace io
{

/*BEGIN*/

class Transform
{
public:
    Transform();
    Transform(const ALLEGRO_TRANSFORM &transform);
    Transform& operator=(const ALLEGRO_TRANSFORM &transform);
    ALLEGRO_TRANSFORM to_allegro_transform() const;
    void identity();
    void invert();
    Transform inverted() const;
    void use();
    void translate(Vector2f position);
    void scale(Vector2f factor);
    void rotate(float angle);
    Vector2f transform_coordinates(Vector2f coordinates);
private:
    ALLEGRO_TRANSFORM t;
};

/*END*/

} // namespace io