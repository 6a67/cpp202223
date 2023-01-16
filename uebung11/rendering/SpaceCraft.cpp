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

namespace asteroids
{

SpaceCraft::SpaceCraft(const std::string &filename, const Vector3f& position, float movespeed, float rotatespeed)
    : m_movespeed(movespeed), m_rotatespeed(rotatespeed), m_autopilot(false), m_stoped(false), m_started(false)
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
    if(keyStates[SDL_SCANCODE_N])
    {
        if(!m_autopilot)
        {
            if(m_started)
            {
                m_thread.join();
                m_started = false;
            }
            navigate();
        }
    }
}

void SpaceCraft::render()
{
    m_mesh->render();
}

void SpaceCraft::calculate(Vector3f dest)
{
    // destination
    Vector3f a = m_mesh->getXAxis();
    Vector3f b = dest - m_mesh->getPosition();
    b.normalize();
        
    // cross product a x b
    Vector3f axis = cross(a, b);
        
    //  a * b
    float numerator = a * b;
        
    // |a|
    float normA = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
        
    // |b|
    float normB = sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);
        
    // |a| * |b|
    float denominator = normA * normB;
        
    //acos in Degree
    float angle = (acos(numerator/denominator));
        
    // Against the 'NaN's!
    if ((angle == angle) && (axis[0] == axis[0]) && (axis[1] == axis[1]) && (axis[2] == axis[2]))
    {
        m_mesh->rotate(axis, angle + M_PI);
    }
}

void SpaceCraft::setNavigationPath(const std::list<Vector3f>& list)
{
    m_navigationList = list;
}

void SpaceCraft::navigate()
{
    if(m_navigationList.size())
    {
        // autopilot is on
        m_autopilot = true;
        std::cout << "Start autopilot" << std::endl;

        // start the computer
        m_thread = std::thread(&SpaceCraft::run, this);
        m_started = true;
    }
    else
    {
        cout << "No path to fly" << endl;
    }
}

void SpaceCraft::navigate(std::list<Vector3f> list)
{
    setNavigationPath(list);
    navigate();
}
    
bool SpaceCraft::getAutopilotState()
{
    // return the state of autopilot
    return m_autopilot;
}
    
    
void SpaceCraft::run()
{
    // set the iteration at the beginning of the list
    m_iter = m_navigationList.begin();
        
    // get all coordinates
    while (!m_stoped && m_iter != m_navigationList.end())
    {
        // not at the destination
        while(!m_stoped && m_mesh->getPosition().dist(*m_iter) > 10)
        {

            // calculate the new course
            calculate(*m_iter);
                
            // and fly
            m_mesh->move(Renderable3D::ACCEL, -0.1);

            // (not to fast!)
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }

        m_iter++;
    }
       
    // turn the autopilot off
    m_autopilot = false;
} 

bool SpaceCraft::hasMesh() const
{
    return m_mesh != nullptr;
}

void SpaceCraft::stop()
{
    if(!m_autopilot && !m_started)
    {
        return;
    }

    m_stoped = true;
    m_thread.join();
    m_stoped = false;
    m_autopilot = false;
    m_started = false;
}

SpaceCraft::~SpaceCraft()
{
    stop();
}

} // namespace asteroids
