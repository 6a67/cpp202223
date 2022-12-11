#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Vector.hpp"

#include "Renderable3D.hpp"

namespace asteroids
{

class Sphere : public Renderable3D
{
public:
    /**
     * @brief Construct a new Sphere object
     *
     * @param position   Initial position of the sphere
     * @param radius     Radius
     * @param numSides   Number of horizontal intersections
     * @param numStack   Number of vertical intersections
     */
    Sphere(const Vector& position, float radius, int numSides = 10, int numStack = 10);
    
    /// Renders the sphere at the given position
    virtual void render();

protected:
    /// Position
    Vector m_position;

    /// Radius
    float m_radius;

    /// Number of horizontal intersections
    int m_numSides;

    /// Number of vertical intersections
    int m_numStacks;


};


} // namespace asteroids
#endif // SPHERE_HPP