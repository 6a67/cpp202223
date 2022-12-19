/*
 *  SpaceCraft.hpp
 *
 *  Created on: Nov. 24 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __SpaceCraft_HPP__
#define __SpaceCraft_HPP__

#include "TriangleMesh.hpp"
#include <SDL2/SDL.h>

namespace asteroids
{
/**
 * @brief A class to render a cicle to the screen
 * 
 */
class SpaceCraft 
{
public:
    /**
     * @brief Construct a new SpaceCraft object
     * 
     * @param filename the filename of the Trianglemesh
     * @param position the start position
     * @param movespeed movespeed for the key handling
     * @param rotatespeed rotatespeed for the key handling
     */
    SpaceCraft(const std::string& filename, const Vector3f& position, float movespeed, float rotatespeed);

    /// dtor
    virtual ~SpaceCraft();

    /**
     * @brief moves and rotates the mesh
     * 
     * @param keyStates the SDL Keyinput
     */
    void handleKeyInput(const Uint8* keyStates);

    /// renders the SpaceCraft
    void render();

    /**
     * @brief check if the SpaceCraft has a valid mesh
     * 
     * @return true if mesh is valid
     * @return false if mesh is not valid
     */
    bool hasMesh() const;

private:
    TriangleMesh* m_mesh;
    float m_movespeed;
    float m_rotatespeed;
};

} // namespace asteroids

#endif