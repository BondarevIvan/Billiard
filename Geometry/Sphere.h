#pragma once
#include "Primitive.h"

namespace Math_NS
{
    class Sphere : public Primitive
    {
    public:
        Sphere() = default;
        Sphere(const Sphere&) = default;
        bool collisionWithRay(
            const Vector3d& i_origin,
            const Vector3d& i_direction,
            Vector3d* o_collision = nullptr) const;
    private:
        double d_radius;
        Vector3d d_center;
    };
};