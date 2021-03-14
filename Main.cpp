#include <Geometry/Rectangle3D.h>

#include <iostream>

int main()
{
    Math_NS::Plane plane(Math_NS::yAxis<double>(), 0);
    Math_NS::Vector3d collision;
    Math_NS::Rectangle3D rect(plane, 1, 1, 1);
    if (!rect.collisionWithRay({}, Math_NS::yAxis<double>(), &collision))
    {
        std::cout << "Error\n";
        std::cout << collision[0] << ' ' << collision[1] << ' ' << collision[2] << std::endl;
    } else
    {
        std::cout << collision[0] << ' ' << collision[1] << ' ' << collision[2] << std::endl;
    }
    return 0;
}