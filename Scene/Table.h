#pragma once
#include "Thing3D.h"

#include <Geometry/Rectangle3D.h>

namespace Scene_NS
{
    class Table : public Thing3D
    {
    public:
        Table(Thing3D* i_parent, const Math_NS::Rectangle3D& i_rectangle);
        const Math_NS::Rectangle3D* rectangle() const;
        bool onTable(const Math_NS::Vector3d& i_point) const;
    };
}