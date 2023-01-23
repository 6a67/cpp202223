/*
 *  Renderable2D.cpp
 *
 *  Created on: Nov. 24 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "Renderable2D.hpp"
#include "view/MainWindow.hpp"   
namespace asteroids
{ 

void Renderable2D::begin2D()
{
    // Enter modelview mode and save current view
    // matrix. Set transformation to indentity to 
    // 'undo' current look at transformation
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
  
    // Enter projection mode and set ortho projection
    // according to current window size
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(
        0.0f, m_mainWindow->width(), 
        m_mainWindow->height(), 
        0.0f, -10.0f, 10.0f);
}

void Renderable2D::end2D()
{
    // Delete current ortho projection, enter model
    // view mode and restore previous look at matrix
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Renderable2D::setColor(float r, float g, float b)
{
    m_r = r;
    m_g = g;
    m_b = b;
}

} // namespace asteroids
