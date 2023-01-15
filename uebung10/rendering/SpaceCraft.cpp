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
#include <algorithm>

namespace asteroids
{

SpaceCraft::SpaceCraft(const std::string &filename, const Vector3f& position, float movespeed, float rotatespeed)
    : m_movespeed(movespeed), m_rotatespeed(rotatespeed)
{
    m_mesh = TriangleMeshFactory::instance().getMesh(filename);
    if(m_mesh)
    {
        m_mesh->setPosition(position);
    }
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
    if (keyStates[SDL_SCANCODE_SPACE])
    {
        shoot();
    }
}

void SpaceCraft::render()
{
    m_mesh->render();
    // auto it = std::remove_if(m_bullets.begin(), m_bullets.end(), [](Bullet* b){return !b->isAlive();});
    // m_bullets.erase(it, m_bullets.end());
    // for(auto bullet : m_bullets)
    // {
    //     bullet->render();
    // }

    auto it = m_bullets.begin();
    while(it != m_bullets.end())
    {
        if(!(*it)->isAlive())
        {
            it = m_bullets.erase(it);
        }
        else
        {
            (*it)->render();
            it++;
        }
    }
}

bool SpaceCraft::hasMesh() const
{
    return m_mesh != nullptr;
}

SpaceCraft::~SpaceCraft()
{

}

void SpaceCraft::shoot()
{
    // set pos to the pos to the cannon
    Vector3f pos = m_mesh->getPosition();
    pos += m_mesh->getXAxis() * -160;
    pos += m_mesh->getZAxis() * -40;

    Bullet::Ptr bullet(new Bullet(pos, m_mesh->getXAxis() * -1 * 0.5));
    m_bullets.push_back(bullet);
    bullet->start();
}

} // namespace asteroids
