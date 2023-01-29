#ifndef PHYSICALOBJECT_HPP
#define PHYSICALOBJECT_HPP

#include "Transformable.hpp"
#include "rendering/Renderable.hpp"
#include "rendering/ParticleEffect.hpp"

namespace asteroids
{

class PhysicalObject
: public Transformable
, public Renderable
{
public:
    using Ptr = std::shared_ptr<PhysicalObject>;

    explicit PhysicalObject(float radius)
    : m_radius(radius)
    {
    }

    PhysicalObject() = default;

    void render();

    bool collision(PhysicalObject::Ptr& other);

    virtual ~PhysicalObject() = default;

    virtual float getScale() const { return 1; }

protected:
    /// Radius
    float m_radius;

    /// Pointer to Renderable to render the object
    Renderable::Ptr m_renderable;
};

}  // namespace asteroids

#endif  // PHYSICALOBJECT_HPP
