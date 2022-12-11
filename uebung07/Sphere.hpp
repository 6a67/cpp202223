//
// Created by sascha on 10.12.22.
//

#ifndef CPP18_ASTEROIDS_SPHERE_HPP
#define CPP18_ASTEROIDS_SPHERE_HPP

#include "Vector.hpp"

#include "Renderable3D.hpp"

namespace asteroids
{
class Sphere : public Renderable3D
{
public:
    Sphere(const Vector& position, float radius, int numSides = 10, int numStack = 10);

    /// Renders the sphere at the given position
    void render() override;

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

#endif //CPP18_ASTEROIDS_SPHERE_HPP
