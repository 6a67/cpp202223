/*
 *  SpaceCraft.cpp
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "SpaceCraft.hpp"
#include "io/TriangleMeshFactory.hpp"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace asteroids
{

SpaceCraft::SpaceCraft(const std::string &filename, const Vector3f& position, float movespeed, float rotatespeed): PhysicalObject(100)
{
    m_renderable = TriangleMeshFactory::instance().getMesh(filename);
    m_speed = movespeed;
    m_rotationSpeed = rotatespeed;
    if(m_renderable)
    {
       setPosition(position);
    }
}

bool SpaceCraft::hasMesh() const
{
    return m_renderable != nullptr;
}

SpaceCraft::~SpaceCraft()
{
 
}

} // namespace asteroids
