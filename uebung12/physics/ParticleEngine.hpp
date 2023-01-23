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
/**
 * ParticleEngine.h
 *
 *  @date Jan 10, 2013
 *  @author Thomas Wiemann
 */

#ifndef PARTICLEENGINE_H_
#define PARTICLEENGINE_H_

#include <list>

#include "rendering/Renderable.hpp"
#include "rendering/ParticleEffect.hpp"

namespace asteroids
{

/**
 * @brief   Class to render particle effects
 */
class ParticleEngine : public Renderable
{
public:

    /**
     * @brief   Ctor
     */
    ParticleEngine() = default;

    /**
     * @brief   Adds an @ref ParticleEffect to the engine
     * @param   e   The new effect
     */
    void addEffect(ParticleEffect::Ptr e);

    /**
     * @brief   Renders all particle effects
     */
    void render();

    /**
     * @brief   Ctor.
     */
    virtual ~ParticleEngine() = default;

    /**
     * @brief   Main loop. Checks if an effect has ended and updates to
     *          list of active effects
     */
    void process();

private:

    /// List of active @ref ParticleEffects
    std::list<ParticleEffect::Ptr>     m_effects;
};

} /* namespace asteroids */
#endif /* PARTICLEENGINE_H_ */
