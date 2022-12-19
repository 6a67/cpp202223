/*
 *  Asteroid.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */
#ifndef ASTEROID_HPP_
#define ASTEROID_HPP_

// Asteroid Project includes
#include "TexturedMesh.hpp"

// Std C++ includes
#include <cstdlib>

namespace asteroids
{
/**
 * @brief  Representation of an asteroid
 */
class Asteroid: public Renderable3D
{
public:

    /**
     * @brief   Ctor.
     * @param   start_position   Position of the fighter that shoots this Asteroid
     * @param   scale            Scaling factor to vary the asteroid's size
     */
    Asteroid(TexturedMesh* mesh, Vector3f start_position, float scale);

    Asteroid(const Asteroid& other);

    Asteroid& operator=( Asteroid& rhs );

    /**
     * @brief   Ctor.
     */
    Asteroid();

    virtual ~Asteroid();

    /**
     * @brief   Renders the asteroid
     */
    virtual void render();

protected:

    /// The mesh struture to represent the asteroid
    TexturedMesh*   m_mesh;

    /// Scaling factor
    float           m_scale;
};

}
#endif /* ASTEROID_HPP_ */
