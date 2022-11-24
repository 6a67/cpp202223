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
    m_l = {0,0,-1};
    m_up = {0,1,0};
    m_rot = {0,PI,0};

}

Camera::Camera()
{
    m_initial = {0,0,1};
    m_l = {0,0,-1};

    m_turnSpeed = 1;
    m_moveSpeed = 1;
    m_up = {0,1,0};


}

void Camera::move(CameraMovement dir)
{
    switch(dir)
    {
        case FORWARD:
            m_trans.x += m_moveSpeed * sin(m_rot.y);
            m_trans.z -= m_moveSpeed * cos(m_rot.y);
            break;
        case BACKWARD:
            m_trans.x -= m_moveSpeed * sin(m_rot.y);
            m_trans.z += m_moveSpeed * cos(m_rot.y);
        default:
            break;

    }

}

void Camera::turn(CameraMovement dir)
{
    switch(dir)
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
}


void Camera::apply()
{
    // Rotate the camera to the left using gluLookAt
    // gluLookAt(
    //     0,0,0,
    //     sin(0.01), 0, - cos(0.01),
    //     0,1,0);


    // gluLookAt(
    //     m_trans.x, 0, m_trans.z,
    //     0, 0, -1,
    //     0, 1, 0
    // );

    glLoadIdentity();
    // gluLookAt(0.0, 0.0, -750.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

    m_l.x = m_initial.x + m_trans.x + sin(m_rot.y);
    m_l.y = m_initial.y + m_trans.y + sin(m_rot.x);
    m_l.z = m_initial.z + m_trans.z - cos(m_rot.y);

    gluLookAt(
        m_initial.x + m_trans.x, m_initial.y, m_initial.z + m_trans.z,
        m_l.x, m_l.y, m_l.z,
        0,1,0
    );
    return;
}

} // namespace asteroids
/// TODO: IMPLEMENT CAMERA HERE!
