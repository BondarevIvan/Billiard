#pragma once
#include "Vector.h"
#include "Ray3D.h"

namespace Math_NS
{
    class Primitive
    {
    public:
        Primitive() = default;
        Primitive(const Primitive&) = default;
        virtual bool collisionWithRay(
            const Vector3d& i_origin,
            const Vector3d& i_direction,
            Vector3d* o_collision = nullptr) const = 0;
        bool collisionWithRay(
            const Ray& i_ray,
            Vector3d* o_collision = nullptr) const;
    };
}