/*
 *  ParticleEngine.cpp
 *
 *  @date 19.01.2019
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2019 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */


#include "ParticleEngine.hpp"

#include <iostream>
using namespace std;

namespace asteroids
{

void ParticleEngine::addEffect(ParticleEffect::Ptr e)
{
    m_effects.push_back(e);
}

void ParticleEngine::render()
{
    std::list<ParticleEffect::Ptr>::iterator it;
    for(it = m_effects.begin(); it != m_effects.end(); it++)
    {
        (*it)->render();   
    }   
}

void ParticleEngine::process()
{
    std::list<ParticleEffect::Ptr>::iterator it;
    
    for(it = m_effects.begin(); it != m_effects.end(); it++)
    {
        if((*it)->update())
        {
            it = m_effects.erase(it);
        }        
    }
}

} /* namespace asteroids */
