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

Camera::Camera(const Vector& position, float turnSpeed, float moveSpeed)
{
    m_turnSpeed = turnSpeed;
    m_moveSpeed = moveSpeed;

    m_initial = position;
    m_l       = { 0, 0, -1 };
    m_up      = { 0, 1, 0 };
    m_rot     = { 0, PI, 0 };
}

Camera::Camera()
{
    m_turnSpeed = 1;
    m_moveSpeed = 1;

    m_initial = { 0, 0, 0 };
    m_l       = { 0, 0, -1 };
    m_up      = { 0, 1, 0 };
    m_rot     = { 0, PI, 0 };
}

void Camera::move(CameraMovement dir)
{
    /* sum all values calculated to normalize the vector */
    double sum = std::abs(sin(m_rot.y)) + std::abs(sin(m_rot.x) * cos(m_rot.y))
                 + std::abs(cos(m_rot.x) * cos(m_rot.y));
    /* norm factor then used for normalization */
    double norm = m_moveSpeed / sum;

    switch (dir)
    {
        case FORWARD:
            m_trans.x += m_moveSpeed * norm * sin(m_rot.y);
            m_trans.y -= m_moveSpeed * norm * sin(m_rot.x) * cos(m_rot.y);
            m_trans.z -= m_moveSpeed * norm * cos(m_rot.x) * cos(m_rot.y);
            break;
        case BACKWARD:
            m_trans.x -= m_moveSpeed * norm * sin(m_rot.y);
            m_trans.y += m_moveSpeed * norm * sin(m_rot.x) * cos(m_rot.y);
            m_trans.z += m_moveSpeed * norm * cos(m_rot.x) * cos(m_rot.y);
            break;
        default:
            break;
    }
}

void Camera::turn(CameraMovement dir)
{
    switch (dir)
    {
        case LEFT:
            m_rot.y -= m_turnSpeed;
            break;
        case RIGHT:
            m_rot.y += m_turnSpeed;
            break;
        case UP:
            m_rot.x += m_turnSpeed;
            break;
        case DOWN:
            m_rot.x -= m_turnSpeed;
            break;
        default:
            break;
    }

    /* Limit the rotation to the range [0, 2PI[ */
    if (m_rot.x > 2 * PI)
    {
        m_rot.x -= 2 * PI;
    }
    else if (m_rot.x < 0)
    {
        m_rot.x += 2 * PI;
    }

    if (m_rot.y > 2 * PI)
    {
        m_rot.y -= 2 * PI;
    }
    else if (m_rot.y < 0)
    {
        m_rot.y += 2 * PI;
    }

    if (m_rot.z > 2 * PI)
    {
        m_rot.z -= 2 * PI;
    }
    else if (m_rot.z < 0)
    {
        m_rot.z += 2 * PI;
    }
}


void Camera::apply()
{
    /* Reset the current matrix */
    glLoadIdentity();

    /* Calculate the new look vector */
    m_l.x = m_initial.x + m_trans.x + sin(m_rot.y);
    m_l.y = m_initial.y + m_trans.y - sin(m_rot.x) * cos(m_rot.y);
    m_l.z = m_initial.z + m_trans.z - cos(m_rot.x) * cos(m_rot.y);

    /* Silly effect to turn the image upside down if it is rotated more than 90 degrees */
    if (m_rot.x > PI / 2 && m_rot.x < 3 * PI / 2)
    {
        m_up.x = 0;
        m_up.y = -1;
        m_up.z = 0;
    }
    else
    {
        m_up.x = 0;
        m_up.y = 1;
        m_up.z = 0;
    }

    /* Apply the new camera position */
    gluLookAt(m_initial.x + m_trans.x,
              m_initial.y + m_trans.y,
              m_initial.z + m_trans.z,
              m_l.x,
              m_l.y,
              m_l.z,
              m_up.x,
              m_up.y,
              m_up.z);
    return;
}

}  // namespace asteroids
