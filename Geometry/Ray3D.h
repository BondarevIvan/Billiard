#pragma once
#include "Vector.h"

namespace Math_NS
{
    class Ray
    {
    public:
        Ray() = default;
        Ray(
            const Math_NS::Vector3d& i_origin,
            const Math_NS::Vector3d& i_direction);
        Ray(const Ray&) = default;
        const Math_NS::Vector3d& origin() const;
        const Math_NS::Vector3d& direction() const;
        bool contain(const Math_NS::Vector3d& i_point) const;
    private:
        Math_NS::Vector3d d_origin;
        Math_NS::Vector3d d_direction;
    };
}