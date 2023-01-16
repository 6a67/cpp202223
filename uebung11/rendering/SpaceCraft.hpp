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
//#include "TexturedMesh.hpp"
#include "math/Vector.hpp"
#include <SDL2/SDL.h>
#include <list>
#include <thread>
#include <memory>

namespace asteroids
{
/**
 * @brief A class to render a cicle to the screen
 * 
 */
class SpaceCraft //: public TexturedMesh
{
public:

    using Ptr = std::shared_ptr<SpaceCraft>;

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
     * @brief Start the engine!
     */
    void run();
    
    /**
     * @brief Calculates the new course
     * @param dest current destination
     */
    void calculate(Vector3f dest);

    /**
     * @brief Set the path for navigation
     * 
     * @param list List of points, which represents the navigation path
     */
    void setNavigationPath(const std::list<Vector3f>& list);

    /**
     * @brief Start the autopilot
     */
    void navigate();

    /**
     * @brief Start the autopilot
     * @param list list with the coordinates
     */
    void navigate(std::list<Vector3f> list);
    
    /**
     * @brief Getter-method for the autopilot state
     * @return the autopilot state
     */
    bool getAutopilotState();

    /**
     * @brief check if the SpaceCraft has a valid mesh
     * 
     * @return true if mesh is valid
     * @return false if mesh is not valid
     */
    bool hasMesh() const;

    Vector3f getPosition() const { return m_mesh->getPosition(); }

private:
    /**
     * @brief Stop the current navigation;
     */
    void stop();

    TriangleMesh::Ptr m_mesh;
    float m_movespeed;
    float m_rotatespeed;

    // List with the coordinates for the autopilot
    std::list<Vector3f> m_navigationList;
    
    // Iterator for the list
    std::list<Vector3f>::iterator m_iter;
    
    // state of the autopilot
    bool m_autopilot;

    // A thread for auto piloting
    std::thread m_thread;

    // Flag to stop the navigation
    bool m_stoped;
    // Flag to represent, if the thread was started
    bool m_started;
};

} // namespace asteroids

#endif