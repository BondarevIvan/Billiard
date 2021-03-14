#include "Plane.h"

namespace Math_NS
{
    Plane::Plane(const Vector3d& i_normal, const Vector3d& i_onPlane)
        : d_normal(i_normal)
    {
        d_normal.normalize();
        d_bias = -(d_normal * i_onPlane);
    }

    Plane::Plane(const Vector3d& i_normal, DoubleType_ i_bias)
        : d_normal(i_normal)
        , d_bias(i_bias)
    {
        const auto mod = d_normal.mod();
        assert(mod > std::numeric_limits<double>::epsilon());
        d_bias /= mod;
        d_normal /= mod;
    }
    Plane::Plane(
        const Vector3d& i_first,
        const Vector3d& i_second,
        const Vector3d& i_third)
        : Plane((i_first - i_second) ^ (i_first - i_third), i_first)
    {
    }
    PositionPoint Plane::positionAboutThis(const Vector3d& i_point) const
    {
        static const DoubleType_ Eps = 0.00001;
        auto dst = (i_point * d_normal + d_bias);
        if (dst > Eps)
            return PositionPoint::Up;
        if (dst < -Eps)
            return PositionPoint::Down;
        return PositionPoint::On;
    }
    bool Plane::onPlane(const Vector3d& i_point) const
    {
        return positionAboutThis(i_point) == PositionPoint::On;
    }

    bool equal(double i_first, double i_second)
    {
        return std::abs(i_first - i_second) < std::numeric_limits<double>::epsilon();
    }

    BasisPlane Plane::createBasis() const
    {
        BasisPlane basis;
        createBasis(basis);
        return basis;
    }

    void Plane::createBasis(BasisPlane& o_basis) const
    {
        auto& firstAxis = o_basis.firstAxis;
        /*
            (x, y, z) - вектор
            (-y, x, 0) - вектор перпендикулярный первому
            если x или y != 0, то (-y, x, 0) перпендикулярен первому
            иначе (1, 0, 0) - перпендикулярен первому
        */
        firstAxis[0] = -d_normal[1];
        firstAxis[1] = d_normal[0];
        firstAxis[2] = 0.;
        firstAxis.normalize();
        if (equal(firstAxis.modSqr(), 0.))
        {
            firstAxis = Math_NS::xAxis<double>();
        }
        o_basis.secondAxis = firstAxis ^ d_normal;
    }

    bool Plane::parallelProjection(
        const Vector3d& i_point,
        const Vector3d& i_direction,
        Vector3d& o_projection) const
    {
        // d_normal * projection + d_bias = 0
        // projection + i_direction * t = i_point
        // d_normal * (i_point - i_direction * t) + d_bias = 0
        // t * d_normal * i_direction = d_normal * i_point + d_bias
        auto scalarNormalDir = d_normal * i_direction;
        if (std::abs(scalarNormalDir) <
            std::numeric_limits<double>::epsilon())
        {
            return false;
        }
        double t = (d_normal * i_point + d_bias) / scalarNormalDir;
        o_projection = i_point - i_direction * t;
        return true;
    }

    bool Plane::centralProjection(
        const Vector3d& i_point,
        const Vector3d& i_center,
        Vector3d& o_projection) const
    {
        if (onPlane(i_point) && onPlane(i_center))
            return false;
        if (onPlane(i_center))
        {
            o_projection = i_center;
            return true;
        }
            
        if (onPlane(i_point))
        {
            o_projection = i_point;
            return true;
        }
        const auto rayDirection = (i_point - i_center).norm();
        /* 
            d_normal * o_projection + d_bias = 0
            o_projection = i_point + t * rayDirection
            d_normal * (i_point + t * rayDirection) + d_bias = 0
            t * (d_normal, rayDirection) = -d_bias - d_normal * i_point
        */
        const auto scalar = (d_normal * rayDirection);
        if (std::abs(scalar) < std::numeric_limits<double>::epsilon())
        {
            return false;
        }
        const auto t = -(d_bias + d_normal * i_point) / scalar;
        o_projection = i_point + rayDirection * t;
        return true;
    }
    Plane::DoubleType_ Plane::bias() const { return d_bias; }
    const Vector3d& Plane::normal() const { return d_normal; }

    bool constructPlane(
        const Math_NS::Vector3d& i_first,
        const Math_NS::Vector3d& i_second,
        const Math_NS::Vector3d& i_third,
        Math_NS::Plane& o_plane)
    {
        const auto fs = (i_second - i_first).norm();
        const auto ft = (i_third - i_first).norm();
        if (fs == Math_NS::Vector3d{} || ft == Math_NS::Vector3d{})
            return false;
        if (fs == ft || fs == -ft)
            return false;
        auto normal = fs ^ ft;
        o_plane = Math_NS::Plane(normal, i_first);
        return true;
    }

    Vector3d Plane::zero() const
    {
        return -d_normal * d_bias;
    }

}