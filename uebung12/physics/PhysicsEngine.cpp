
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
    m_trails.push_back(ParticleEffect::createBulletTail(bullet->getPosition(), bullet->direction(), 99999));
}


void PhysicsEngine::process()
{
    // Iterate over all bullets und check wether they
    // collide with one of the active physical objects
    // If they collide, remove the bullet and object-

    auto trail = m_trails.begin();
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
            m_stillTrails.push_back(std::pair<ParticleEffect::Ptr, int>(*trail, 300));
            trail = m_trails.erase(trail);
            continue;
        }

        for (auto objIt = m_objects.begin(); objIt != m_objects.end();)
        {
            auto& object = *objIt;
            if (bullet->collision(object))
            {
                m_explosions.push_back(ParticleEffect::createExplosionSphere(object->getPosition()));
                it = m_bullets.erase(it);
                m_stillTrails.push_back(std::pair<ParticleEffect::Ptr, int>(*trail, 300));
                trail = m_trails.erase(trail);
                objIt = m_objects.erase(objIt);
                break;
            }
            else
            {
                objIt++;
            }
        }
        it++;
        trail++;
    }

    for(auto it = m_explosions.begin(); it != m_explosions.end();)
    {
        if((*it)->update())
        {
            it = m_explosions.erase(it);
            continue;
        }
        it++;
    }

    for(auto it = m_trails.begin(); it != m_trails.end();)
    {
        if((*it)->update())
        {
            it = m_trails.erase(it);
            continue;
        }
        it++;
    }

    for(auto it = m_stillTrails.begin(); it != m_stillTrails.end();)
    {
        if(it->second > 0)
        {
            it->first->update();
            it->second--;
            it++;
        }
        else
        {
            it = m_stillTrails.erase(it);
        }
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

    for(auto& explosion : m_explosions)
    {
        explosion->render();
    }

    for(auto& trail : m_trails)
    {
        trail->render();
    }

    for(auto& trail : m_stillTrails)
    {
        trail.first->render();
    }
}

} /* namespace asteroids */
