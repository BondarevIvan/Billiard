#include "Sphere.h"

#include <optional>
#include <algorithm>

namespace Math_NS
{
    struct EquationSolution
    {
        std::optional<double> firstRoot;
        std::optional<double> secondRoot;
    };
    // ax^2 + bx + c
    EquationSolution solve(double a, double b, double c)
    {
        if (std::abs(a) < std::numeric_limits<double>::epsilon())
        {
            return EquationSolution{ {}, {} };
        }
        const auto D = b * b - 4 * a * c;
        if (D < 0)
            return EquationSolution{ {}, {} };
        EquationSolution solution;
        solution.firstRoot = (-b + sqrt(D)) / (2 * a);
        solution.secondRoot = (-b - sqrt(D)) / (2 * a);
        return solution;
    }
    bool Sphere::collisionWithRay(
        const Vector3d& i_origin,
        const Vector3d& i_direction,
        Vector3d* o_collision) const
    {
        /*
            collision = i_origin + i_direction * t;
            (collision - d_center, collision - d_center) = d_radius * d_radius
            ((i_origin - d_center) + i_direction * t, (i_origin - d_center) + i_direction * t) = d_radius * d_radius
            (a + b * x, a + b * x) = c
            a = (i_origin - d_center), b = i_direction
            c = d_radius * d_radius
            (a, a) + (a, b) * 2x + (b, b) * x^2 = c
        */
        const auto collisions = solve(
            i_direction * i_direction,
            i_direction * (i_origin - d_center) * 2,
            d_radius * d_radius);
        std::vector<double> positiveCoords;
        if (collisions.firstRoot && *collisions.firstRoot >= 0)
            positiveCoords.push_back(*collisions.firstRoot);
        if (collisions.secondRoot && *collisions.secondRoot >= 0)
            positiveCoords.push_back(*collisions.secondRoot);
        bool hasCollision = !positiveCoords.empty();
        if (!hasCollision)
            return false;
        std::sort(positiveCoords.begin(), positiveCoords.end());
        if (o_collision)
            *o_collision = i_origin + i_direction * positiveCoords.front();
        return true;
    }

}