#include <GL/glew.h>
#include "PhysicalObject.hpp"

namespace asteroids
{

void PhysicalObject::render()
{
    // Compute transformation matrix
    computeMatrix();

    // Push matrix and set transformation and scaling
    glPushMatrix();
    glMultMatrixf(m_transformation.getData());

    std::cout << "PhysicalObject::render()" << std::endl;

    if(m_renderable)
    {
        m_renderable->render();
    }
    glPopMatrix();
}

bool PhysicalObject::collision(PhysicalObject::Ptr& other)
{
    Vector<float> diff = getPosition();
    Vector<float> diff2 = other->getPosition();
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

    return dist < m_radius + other->m_radius;
}

} // namespace asteroids