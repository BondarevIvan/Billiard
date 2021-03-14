#include "Thing3D.h"

#include <stack>

namespace Scene_NS
{
    Thing3D::Thing3D()
        : d_children{}
        , d_parent{}
        , d_transform(Math_NS::CommonSizeSpace)
        , d_inverseTransform(Math_NS::CommonSizeSpace)
    {
    }

    void Thing3D::setParent(Thing3D* i_parent)
    {
        if (d_parent)
            d_parent->removeChild(this);
        d_parent = i_parent;
        if (i_parent)
        {
            i_parent->addChild(this);
        }
    }

    void Thing3D::removeChild(Thing3D* i_child)
    {
        auto it = d_children.begin();
        for (; it != d_children.end(); ++it)
        {
            if (*it == i_child)
                break;
        }
        if (it != d_children.end())
            d_children.erase(it);
    }

    const Math_NS::Matrix& Thing3D::inverseTransform() const
    {
        return d_inverseTransform;
    }

    void Thing3D::addChild(Thing3D* i_thing)
    {
        if (i_thing)
        {
            d_children.push_back(i_thing);
            i_thing->d_parent = this;
        }
    }
    Thing3D* Thing3D::parent()
    {
        return d_parent;
    }
    const Thing3D* Thing3D::parent() const
    {
        return d_parent;
    }
    std::vector<Thing3D*>& Thing3D::children()
    {
        return d_children;
    }
    const std::vector<Thing3D*>& Thing3D::children() const
    {
        return d_children;
    }

    const Math_NS::Matrix& Thing3D::localTransform() const
    {
        return d_transform;
    }

    Math_NS::Matrix Thing3D::localToWorldTransform() const
    {
        Math_NS::Matrix localToWorld(Math_NS::CommonSizeSpace);
        const auto* parent = this;
        std::stack<const Thing3D*> pathToRoot;
        while (parent)
        {
            pathToRoot.push(parent);
            parent = parent->d_parent;
        }
        while (!pathToRoot.empty())
        {
            localToWorld *= pathToRoot.top()->localTransform();
            pathToRoot.pop();
        }
        return localToWorld;
    }

    Math_NS::Matrix Thing3D::inverseWorldTransform() const
    {
        Math_NS::Matrix localToWorld(Math_NS::CommonSizeSpace);
        const auto* parent = this;
        std::stack<const Thing3D*> pathToRoot;
        while (parent)
        {
            pathToRoot.push(parent);
            parent = parent->d_parent;
        }
        while (!pathToRoot.empty())
        {
            localToWorld *= pathToRoot.top()->inverseTransform();
            pathToRoot.pop();
        }
        return localToWorld;
    }


    void Thing3D::setTransform(const Math_NS::Matrix& i_transform)
    {
        d_transform = i_transform;
        assert(Math_NS::inverse(d_transform, &d_inverseTransform));
    }

    void Thing3D::setWorldTransform(const Math_NS::Matrix& i_worldTransform)
    {
        // parentWorldTransform * newLocalTransform = i_worldTransform
        // newLocalTransform = inverse(parentWorldTransform) * i_worldTransform
        if (d_parent)
            setTransform(i_worldTransform);
        else
            setTransform(d_parent->inverseWorldTransform() * i_worldTransform);
    }

    Math_NS::Primitive* Thing3D::form()
    {
        return d_form;
    }

    const Math_NS::Primitive* Thing3D::form() const
    {
        return d_form;
    }

    void Thing3D::setForm(Math_NS::Primitive* i_form)
    {
        d_form = i_form;
    }

}