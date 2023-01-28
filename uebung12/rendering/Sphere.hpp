/*
 *  Sphere.hpp
 *
 *  Created on: Nov. 25 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "Renderable.hpp"
#include "physics/Transformable.hpp"

namespace asteroids
{

/**
 * @brief A sphere in 3D space
 * 
 */
class Sphere : public Transformable, public Renderable
{
public:

    using Ptr = std::shared_ptr<Sphere>;

    /**
     * @brief Construct a new Sphere object
     * 
     * @param position      Initial position of the sphere
     * @param radius        Radius
     * @param numSides      Number of horizontal intersections
     * @param numStack      Number of vertical intersections
     */
    Sphere(
        const Vector3f& position, 
        float radius, int numSides = 10, int numStack = 10);

    Sphere() = delete;

    virtual ~Sphere() = default;

    /**
     * @brief Renders the sphere
     * 
     */
    virtual void render() override;

    /// Returns the radius of the sphere
    int radius();

    /// Sets the color of the sphere
    void setColor(float r, float g, float b);

private:

    /// Radius
    float   m_radius;

    /// Number of horizontal intersections
    int     m_numSides;

    /// Number of vertical intersections
    int     m_numStacks;

    /// color
    float m_color[3] = {0.4f, 0.3f, 0.7f};
};

} // namespace asteroids

#endif
