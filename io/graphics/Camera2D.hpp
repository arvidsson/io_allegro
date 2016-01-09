#pragma once

#include "../math/Vector.hpp"
#include <alcpp.hpp>

namespace io
{

class Camera2D
{
public:
    void Use();
    void Reset();

    void MoveTo(float x, float y);
    void MoveBy(float scrollX, float scrollY);
    void ZoomTo(float z);
    void ZoomBy(float z);
    void RotateTo(float r);
    void RotateBy(float r);

    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetZoom() const { return zoom; }
    float GetRotation() const { return rotate; }

    /*
        Converts a world coordinate to screen coordinates.
    */
    Vector<float> ToScreen(float x, float y) const;
    Vector<float> ToScreen(const Vector<float> &coords) const;

    /*
        Converts a screen coordinate to world coordinates.
    */
    Vector<float> ToWorld(float x, float y) const;
    Vector<float> ToWorld(const Vector<float> &coords) const;

private:
    alcpp::Transform GetTransform() const;
    float x = 0.0f, y = 0.0f;
    float zoom = 1.0;
    float rotate = 0.0f;
};

}