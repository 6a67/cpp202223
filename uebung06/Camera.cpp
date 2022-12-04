/*
 *  Camera.cpp
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include <stdio.h>
#include <math.h>
#include <GL/glu.h>

#include "Camera.hpp"

namespace asteroids
{

Camera::Camera(const Vector& pos, const float& turnSpeed, const float& moveSpeed)
{
    /* Init pos */
    m_initial.x = pos.x;
    m_initial.y = pos.y;
    m_initial.z = pos.z;

    m_trans.x = 0.0f;
    m_trans.y = 0.0f;
    m_trans.z = 0.0f;


    /* Init look up vector */
    m_up.x = 0.0f;
    m_up.y = 1.0f;
    m_up.z = 0.0f;

    /* Init look at vector */
    m_l.x = 0.0f;
    m_l.y = 0.0f;
    m_l.z = 0.0f;

    /* Init rotation angles */
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;

    /* Set speed parameters */
    m_turnSpeed = turnSpeed;
    m_moveSpeed = moveSpeed;
}


void Camera::move(const CameraMovement& dir)
{
    switch (dir)
    {
        case FORWARD:
            m_trans.x += m_moveSpeed * sin(m_rot.y);
            m_trans.z += m_moveSpeed * cos(m_rot.y);
            break;
        case BACKWARD:
            m_trans.x -= m_moveSpeed * sin(m_rot.y);
            m_trans.z -= m_moveSpeed * cos(m_rot.y);
            break;
        case LEFT:
            m_trans.x -= m_moveSpeed * sin(PH - m_rot.y);
            m_trans.z -= m_moveSpeed * cos(PH - m_rot.y);
            break;
        case RIGHT:
            m_trans.x += m_moveSpeed * sin(PH + m_rot.y);
            m_trans.z += m_moveSpeed * cos(PH + m_rot.y);
            break;
        case UP:
            m_trans.y += m_moveSpeed;
            break;
        case DOWN:
            m_trans.y -= m_moveSpeed;
            break;
    }
}


void Camera::turn(const CameraMovement& dir)
{
    if (dir == UP)
    {
        if (m_rot.x < PH)
        {
            m_rot.x -= m_turnSpeed;
        }
    }
    else if (dir == DOWN)
    {
        if (m_rot.x < PH)
        {
            m_rot.x += m_turnSpeed;
        }
    }
    else if (dir == LEFT)
    {
        m_rot.y -= m_turnSpeed;
    }

    else if (dir == RIGHT)
    {
        m_rot.y += m_turnSpeed;
    }
}

void Camera::apply()
{
    /* Calc look at vector based on rotation state */
    m_l.x = m_initial.x + m_trans.x + sin(m_rot.y);
    m_l.z = -m_initial.z - m_trans.z - cos(m_rot.y);
    m_l.y = m_initial.y + m_trans.y + sin(m_rot.x);

    /* Clear matrix stack */
    glLoadIdentity();

    /* Apply transformation */
    gluLookAt(m_initial.x + m_trans.x,
              m_initial.y + m_trans.y,
              -m_initial.z - m_trans.z,
              m_l.x,
              m_l.y,
              m_l.z,
              m_up.x,
              m_up.y,
              m_up.z);
}

}  // namespace asteroids
