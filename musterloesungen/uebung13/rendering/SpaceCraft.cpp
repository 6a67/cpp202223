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

void SpaceCraft::handleKeyInput(std::map<Qt::Key, bool>& keyStates)
{
    if (keyStates[Qt::Key_Up])
    {
        m_mesh->rotate(TriangleMesh::YAW, m_rotatespeed);
    }
    if (keyStates[Qt::Key_Down])
    {
        m_mesh->rotate(TriangleMesh::YAW, -m_rotatespeed);
    }
    if (keyStates[Qt::Key_Left])
    {
        m_mesh->rotate(TriangleMesh::ROLL, m_rotatespeed);
    }
    if (keyStates[Qt::Key_Right])
    {
        m_mesh->rotate(TriangleMesh::ROLL, -m_rotatespeed);
    }
    if (keyStates[Qt::Key_W])
    {
        m_mesh->move(TriangleMesh::ACCEL, -m_movespeed);
    }
    if (keyStates[Qt::Key_S])
    {
        m_mesh->move(TriangleMesh::ACCEL, m_movespeed);
    }
    if (keyStates[Qt::Key_A])
    {
        m_mesh->move(TriangleMesh::STRAFE, -m_movespeed);
    }
    if (keyStates[Qt::Key_D])
    {
        m_mesh->move(TriangleMesh::STRAFE, m_movespeed);
    }
    if(keyStates[Qt::Key_Space])
    {
        shoot();
    }
}

struct BulletRenderer
{
    void operator()(Bullet::Ptr& b)
    {
        b->render();
    }
};

struct IsDead
{
    bool operator()(Bullet::Ptr& b)
    {
        return !b->isAlive();
    }
};

void SpaceCraft::render()
{
    m_mesh->render();
    std::for_each(m_bullets.begin(), m_bullets.end(), BulletRenderer());

    auto it = remove_if(m_bullets.begin(), m_bullets.end(), IsDead());
    m_bullets.erase(it, m_bullets.end());
}

bool SpaceCraft::hasMesh() const
{
    return m_mesh != nullptr;
}

void SpaceCraft::shoot()
{
    // Create new bullet
    Bullet::Ptr b_ptr(new Bullet(m_mesh->position(), m_mesh->xAxis()));

    // Start bullet thread and add to list of active bullets
    b_ptr->start();
    m_bullets.push_back(b_ptr);

}

SpaceCraft::~SpaceCraft()
{
 
}

} // namespace asteroids
