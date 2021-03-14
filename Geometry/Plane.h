#pragma once
#include "Vector.h"

#include <functional>

namespace Math_NS
{
    enum class PositionPoint
    {
        Up,
        Down,
        On
    };

    struct BasisPlane
    {
        Math_NS::Vector3d firstAxis;
        Math_NS::Vector3d secondAxis;
    };


    class Plane
    {
    public:
        using DoubleType_ = Vector3d::DoubleType_;
        Plane() = default;
        Plane(const Vector3d& i_normal, const Vector3d& i_onPlane);
        Plane(const Vector3d& i_normal, DoubleType_ i_bias);
        Plane(const Vector3d& i_first,
              const Vector3d& i_second,
              const Vector3d& i_third);
        Plane(const Plane&) = default;
        PositionPoint positionAboutThis(const Vector3d& i_point) const;
        bool onPlane(const Vector3d& i_point) const;

        void createBasis(BasisPlane& o_basis) const;
        BasisPlane createBasis() const;

        bool parallelProjection(
            const Vector3d& i_point,
            const Vector3d& i_direction,
            Vector3d& o_projection) const;

        bool centralProjection(
            const Vector3d& i_point,
            const Vector3d& i_center,
            Vector3d& o_projection) const;
        DoubleType_ bias() const;
        const Vector3d& normal() const;
        Vector3d zero() const;
    private:
        Vector3d d_normal = xAxis<DoubleType_>();
        DoubleType_ d_bias;
    };
    bool constructPlane(
        const Math_NS::Vector3d& i_first,
        const Math_NS::Vector3d& i_second,
        const Math_NS::Vector3d& i_third,
        Math_NS::Plane& o_plane);
}