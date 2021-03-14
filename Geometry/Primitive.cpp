#include "Primitive.h"

namespace Math_NS
{
    bool Primitive::collisionWithRay(
        const Ray& i_ray,
        Vector3d* o_collision) const
    {
        return collisionWithRay(
            i_ray.origin(), 
            i_ray.direction(), 
            o_collision);
    }

}