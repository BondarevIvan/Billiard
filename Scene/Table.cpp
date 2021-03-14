#include "Table.h"

namespace Scene_NS
{
    Table::Table(
        Thing3D* i_parent,
        const Math_NS::Rectangle3D& i_rectangle)
    {
        setForm(new Math_NS::Rectangle3D(i_rectangle));
        setParent(i_parent);
    }
    const Math_NS::Rectangle3D* Table::rectangle() const
    {
        return dynamic_cast<const Math_NS::Rectangle3D*>(form());
    }

    bool Table::onTable(const Math_NS::Vector3d& i_point) const
    {
        return rectangle() && rectangle()->onRect(i_point);
    }

}