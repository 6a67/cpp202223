#ifndef PHYSICALOBJECT_HPP
#define PHYSICALOBJECT_HPP

#include "Transformable.hpp"
#include "rendering/Renderable.hpp"

namespace asteroids
{

class PhysicalObject: public Transformable, public Renderable
{
public:

    using Ptr = std::shared_ptr<PhysicalObject>;

    PhysicalObject(float m_radius): m_radius(m_radius) {};

    PhysicalObject() = default;

    void render();

    bool collision(PhysicalObject::Ptr& other);

    virtual ~PhysicalObject() = default;

protected:
    /// Radius
    float   m_radius;

    /// Pointer to Renderable to render the object
    Renderable::Ptr m_renderable;
};

} // namespace asteroids

#endif // PHYSICALOBJECT_HPP
