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

namespace asteroids
{

SpaceCraft::SpaceCraft(const std::string &filename, const Vector3f& position, float movespeed, float rotatespeed)
    : m_movespeed(movespeed), m_rotatespeed(rotatespeed)
{
    // TODO: Get mesh from TriangleMesh factory and save it 
    // in m_mesh. Set correct intial position
    m_mesh = nullptr;
}

void SpaceCraft::handleKeyInput(const Uint8* keyStates)
{
    if (keyStates[SDL_SCANCODE_UP])
    {
        m_mesh->rotate(TriangleMesh::YAW, m_rotatespeed);
    }
    if (keyStates[SDL_SCANCODE_DOWN])
    {
        m_mesh->rotate(TriangleMesh::YAW, -m_rotatespeed);
    }
    if (keyStates[SDL_SCANCODE_LEFT])
    {
        m_mesh->rotate(TriangleMesh::ROLL, m_rotatespeed);
    }
    if (keyStates[SDL_SCANCODE_RIGHT])
    {
        m_mesh->rotate(TriangleMesh::ROLL, -m_rotatespeed);
    }
    if (keyStates[SDL_SCANCODE_W])
    {
        m_mesh->move(TriangleMesh::ACCEL, -m_movespeed);
    }
    if (keyStates[SDL_SCANCODE_S])
    {
        m_mesh->move(TriangleMesh::ACCEL, m_movespeed);
    }
    if (keyStates[SDL_SCANCODE_A])
    {
        m_mesh->move(TriangleMesh::STRAFE, -m_movespeed);
    }
    if (keyStates[SDL_SCANCODE_D])
    {
        m_mesh->move(TriangleMesh::STRAFE, m_movespeed);
    }
}

void SpaceCraft::render()
{
    if(m_mesh)
    {
        m_mesh->render();
    }
}

bool SpaceCraft::hasMesh() const
{
    return m_mesh != nullptr;
}

SpaceCraft::~SpaceCraft()
{
    if(m_mesh)
    {
        delete m_mesh;
        m_mesh = nullptr;
    }
}

} // namespace asteroids
