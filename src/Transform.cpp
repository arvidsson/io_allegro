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

/*END*/

} // namespace io