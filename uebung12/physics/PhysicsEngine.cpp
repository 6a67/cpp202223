
/*
 *  PhysicsEngine.cpp
 *
 *  @date 19.01.2019
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2019 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */


#include "PhysicsEngine.hpp"

#include <iostream>
using namespace std;

namespace asteroids
{


void PhysicsEngine::addDestroyable(std::shared_ptr<PhysicalObject>& obj)
{
    // Add the object (asteroid) to the list of active objects

    // take ownership of the object and store it in the list
//    m_objects.push_back(std::make_unique<PhysicalObject>(*obj));
    m_objects.push_back(obj);

}

void PhysicsEngine::addBullet(Bullet::Ptr& bullet)
{
    // Add an bullet to the list of active bullets
//    m_bullets.push_back(std::make_unique<Bullet>(*bullet));
    m_bullets.push_back(bullet);
}


void PhysicsEngine::process()
{
    // Iterate over all bullets und check wether they
    // collide with one of the active physical objects
    // If they collide, remove the bullet and object-

    for (auto it = m_bullets.begin(); it != m_bullets.end();)
    {
        auto& bullet = *it;
        if(bullet->isAlive())
        {
            bullet->run();
        }
        else
        {
            it = m_bullets.erase(it);
            continue;
        }

        for (auto objIt = m_objects.begin(); objIt != m_objects.end();)
        {
            auto& object = *objIt;
            if (bullet->collision(object))
            {
                it = m_bullets.erase(it);
                objIt = m_objects.erase(objIt);
                break;
            }
            else
            {
                objIt++;
            }
        }
        it++;
    }

}

void PhysicsEngine::render()
{
   // Render all objects and bullets-

    for (auto& bullet : m_bullets)
    {
         bullet->render();
    }

    for (auto& object : m_objects)
    {
         object->render();
    }
}

} /* namespace asteroids */
