#pragma once
#include "Thing3D.h"

#include <Geometry/Rectangle3D.h>

namespace Scene_NS
{
    class Camera : public Thing3D
    {
    public:
        Camera() = delete;
        Camera(Thing3D* i_parent);
        Math_NS::Vector3d worldUp() const;    // Oy
        Math_NS::Vector3d worldRight() const; // Ox
        Math_NS::Vector3d direction() const;  // Oz
        Math_NS::Vector3d position() const;
//        double yaw() const;
//        double pitch() const;
//        double roll() const;
        const Math_NS::Rectangle3D& photoPlane() const;
        Math_NS::Ray constructRay(
            int i_resolutionWidth,
            int i_resolutionHeight,
            int i_posX, int i_posY);
    private:
        Math_NS::Rectangle3D d_photoPlane;
    };
}