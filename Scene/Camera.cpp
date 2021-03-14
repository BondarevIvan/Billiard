#include "Camera.h"

namespace Scene_NS
{
    Camera::Camera(Thing3D* i_parent)
    {
        setParent(i_parent);
    }

    Math_NS::Vector3d Camera::worldUp() const
    {
        return Math_NS::vectorTransform(localToWorldTransform(), Math_NS::yAxis<double>());
    }

    Math_NS::Vector3d Camera::worldRight() const
    {
        return Math_NS::vectorTransform(localToWorldTransform(), Math_NS::xAxis<double>());
    }

    Math_NS::Vector3d Camera::direction() const
    {
        return Math_NS::vectorTransform(localToWorldTransform(), Math_NS::zAxis<double>());
    }

    Math_NS::Vector3d Camera::position() const
    {
        return Math_NS::pointTransform(localToWorldTransform(), {});
    }
}