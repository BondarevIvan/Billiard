#pragma once
#include <Geometry/Matrix.h>
#include <Geometry/Primitive.h>
#include <vector>
#include <memory>

namespace Scene_NS
{
    class Thing3D
    {
    public:
        Thing3D();
        Thing3D(Thing3D&&) = delete;
        Thing3D(const Thing3D&) = delete;

        Thing3D& operator=(const Thing3D&) = delete;

        void setParent(Thing3D* i_parent);
        void addChild(Thing3D* i_thing);
        Thing3D* parent();
        const Thing3D* parent() const;
        std::vector<Thing3D*>& children();
        const std::vector<Thing3D*>& children() const;
        void removeChild(Thing3D* i_child);
        const Math_NS::Matrix& inverseTransform() const;
        Math_NS::Matrix inverseWorldTransform() const;
        const Math_NS::Matrix& localTransform() const;
        Math_NS::Matrix localToWorldTransform() const;
        void setTransform(const Math_NS::Matrix& i_transform);
        void setWorldTransform(const Math_NS::Matrix& i_worldTransform);
        Math_NS::Primitive* form();
        const Math_NS::Primitive* form() const;
        void setForm(Math_NS::Primitive* i_form);
    private:
        Thing3D* d_parent;
        Math_NS::Primitive* d_form;
        std::vector<Thing3D*> d_children;
        Math_NS::Matrix d_transform;
        Math_NS::Matrix d_inverseTransform;
    };
    template<class Type>
    Type* findByType(Thing3D* i_root, int i_depth)
    {
        if (!i_root) return nullptr;
        if (auto* cast = dynamic_cast<Type*>(i_root))
            return cast;
        if (i_depth == 0) return nullptr;
        for (auto* child : i_root->children())
        {
            if (auto* found = findByType<Type>(i_root, i_depth - 1))
                return found;
        }
        return nullptr;
    }
}