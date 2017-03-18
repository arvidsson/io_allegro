#include "Transform.h"

namespace io
{

/*BEGIN*/

Transform::Transform()
{
    identity();
}

Transform::Transform(const ALLEGRO_TRANSFORM &transform)
{
    al_copy_transform(&t, &transform);
}

Transform& Transform::operator=(const ALLEGRO_TRANSFORM &transform)
{
    al_copy_transform(&t, &transform);
    return *this;
}

ALLEGRO_TRANSFORM Transform::to_allegro_transform() const
{
    return t;
}

void Transform::identity()
{
    al_identity_transform(&t);
}

void Transform::invert()
{
    al_invert_transform(&t);
}

Transform Transform::inverted() const
{
    Transform t = *this;
    t.invert();
    return t;
}

void Transform::use()
{
    al_use_transform(&t);
}

void Transform::translate(Vector2f position)
{
    al_translate_transform(&t, position.x, position.y);
}

void Transform::scale(Vector2f factor)
{
    al_scale_transform(&t, factor.x, factor.y);
}

void Transform::rotate(float angle)
{
    al_rotate_transform(&t, angle);
}

Vector2f Transform::transform_coordinates(Vector2f coordinates)
{
    float x, y;
    al_transform_coordinates(&t, &x, &y);
    return Vector2f{x, y};
}

/*END*/

} // namespace io