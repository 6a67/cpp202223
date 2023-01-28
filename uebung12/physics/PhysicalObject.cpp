#include <GL/glew.h>
#include "PhysicalObject.hpp"
#include "PhysicalObjectScale.hpp"

namespace asteroids
{

template<typename Obj>
struct ObjectTraits
{
    static const bool hasScale = false;
};

template<>
struct ObjectTraits<PhysicalObjectScale>
{
    static const bool hasScale = true;
};


template <typename Derived>
void PhysicalObject<Derived>::render()
{
    // Compute transformation matrix
    computeMatrix();

    // Push matrix and set transformation and scaling
    glPushMatrix();
    glMultMatrixf(m_transformation.getData());

    if(ObjectTraits<Derived>::hasScale)
    {
        // cast this to PhysicalObjectScale and get the scale
        glScalef(static_cast<PhysicalObjectScale*>(this)->getScale(),
                 static_cast<PhysicalObjectScale*>(this)->getScale(),
                 static_cast<PhysicalObjectScale*>(this)->getScale());
    }


    if(m_renderable)
    {
        m_renderable->render();
    }
    glPopMatrix();
}

bool PhysicalObject::collision(PhysicalObject::Ptr& other)
{
    Vector<float> diff = getPosition() - other->getPosition();
    // get value of the distance between the two objects
    float dist = 0;
    dist += diff[0] * diff[0];
    dist += diff[1] * diff[1];
    try {
        dist += diff[2] * diff[2];
    } catch (std::invalid_argument& e) {
        // do nothing
    }
    dist = sqrt(dist);

    if(dist < m_radius + other->m_radius) {
        std::cout << "Collision" << std::endl;
    }

    return dist < m_radius + other->m_radius;
}

} // namespace asteroids