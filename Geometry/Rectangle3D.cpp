#include "Rectangle3D.h"

#include <Geometry/Matrix.h>

namespace Math_NS
{
    Rectangle3D::Rectangle3D(
        const Plane& i_plane,
        double i_halfWidth,
        double i_halfHeight,
        double i_rotation)
        : d_plane(i_plane)
        , d_halfHeight(i_halfHeight)
        , d_halfWidth(i_halfWidth)
        , d_rotation(i_rotation)
    {
    }


    const Plane& Rectangle3D::plane() const
    {
        return d_plane;
    }

    double Rectangle3D::width() const
    {
        return d_halfWidth * 2.;
    }

    double Rectangle3D::height() const
    {
        return d_halfHeight * 2.;
    }

    bool Rectangle3D::collisionWithRay(
        const Vector3d& i_origin,
        const Vector3d& i_direction,
        Vector3d* o_collision) const
    {
        Vector3d collision;
        if (!d_plane.parallelProjection(i_origin, i_direction, collision))
        {
            return false;
        }
        if (o_collision)
            *o_collision = collision;
        return onRect(collision);
    }

    double Rectangle3D::rotation() const
    {
        return d_rotation;
    }
    bool Rectangle3D::onRect(const Vector3d& i_point) const
    {
        Math_NS::BasisPlane basis = d_plane.createBasis();
        double xCoordinate = basis.firstAxis * i_point;
        double yCoordinate = basis.secondAxis * i_point;
        double angle = atan2(yCoordinate, xCoordinate);
        double mod = sqrt(xCoordinate * xCoordinate + yCoordinate * yCoordinate);
        angle -= d_rotation;
        xCoordinate = cos(angle) * mod;
        yCoordinate = sin(angle) * mod;
        if (std::abs(xCoordinate) > d_halfWidth || 
            std::abs(yCoordinate) > d_halfHeight)
            return false;
        return true;
    }

    Vector3d Rectangle3D::localToWorldPoint(const Vector2d& i_coords) const
    {
        const auto basis = d_plane.createBasis();

        const auto rotation = Math_NS::rotationByAxis(d_rotation, d_plane.normal());
        Math_NS::vectorTransform(rotation, basis.firstAxis);
        Math_NS::vectorTransform(rotation, basis.secondAxis);
        return d_plane.zero() + 
               basis.firstAxis * i_coords[0] +
               basis.secondAxis * i_coords[1];
    }

}