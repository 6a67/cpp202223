/*
 *  Rectangle.cpp
 *
 *  Created on: Nov. 24 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "Rectangle.hpp"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
namespace asteroids
{

void Rectangle::render()
{
    begin2D();
    glColor3f(m_r, m_g, m_b);
    glBegin(GL_LINE_LOOP);
    glVertex2d(m_position[0], m_position[1]);
    glVertex2d(m_position[0] + m_dimension[0], m_position[1]);
    glVertex2d(m_position[0] + m_dimension[0], m_position[1] + m_dimension[1]);
    glVertex2d(m_position[0], m_position[1] + m_dimension[1]);
    glEnd();
    end2D();
}

} // namespace asteroids