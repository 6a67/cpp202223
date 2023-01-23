
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
}

void PhysicsEngine::addBullet(Bullet::Ptr& bullet)
{
    // Add an bullet to the list of active bullets
}

void PhysicsEngine::process()
{
    // Iterate over all bullets und check wether they
    // collide with one of the active physical objects
    // If they collide, remove the bullet and object-
}

void PhysicsEngine::render()
{
   // Render all objects and bullets-
}

} /* namespace asteroids */
