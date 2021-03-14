#pragma once
#include "Plane.h"
#include "Primitive.h"

namespace Math_NS
{
    class Rectangle3D : public Primitive
    {
    public:
        Rectangle3D() = default;
        Rectangle3D(
            const Plane& i_plane,
            double i_halfWidth,
            double i_halfHeight,
            double i_rotation);
        Rectangle3D(const Rectangle3D&) = default;
        const Plane& plane() const;
        double width() const;
        double height() const;
        bool collisionWithRay(
            const Vector3d& i_origin,
            const Vector3d& i_direction,
            Vector3d* o_collision = nullptr) const override;
        double rotation() const;
        bool onRect(const Vector3d& i_point) const;
        Vector3d localToWorldPoint(const Vector2d& i_coords) const;
    private:
        Plane d_plane;
        double d_halfWidth;
        double d_halfHeight;
        double d_rotation;
    };
}