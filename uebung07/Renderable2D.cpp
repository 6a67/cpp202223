//
// Created by sascha on 10.12.22.
//
#include "Renderable2D.hpp"

namespace asteroids
{
Renderable2D::Renderable2D(asteroids::MainWindow *mainWindow) : m_mainWindow(mainWindow) {}

void Renderable2D::begin2DRender()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, m_mainWindow->width(), m_mainWindow->height(), 0.0f, -10.0f, 10.0f);

    /// Get current color
    glGetFloatv(GL_CURRENT_COLOR, m_previousColor);

    /// Set color
    glColor3f(m_red, m_green, m_blue);
}

void Renderable2D::end2DRender()
{
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    /// Reset color
    glColor3f(m_previousColor[0], m_previousColor[1], m_previousColor[2]);
}


void Renderable2D::setColor(float r, float g, float b)
{
    m_red   = r;
    m_green = g;
    m_blue  = b;
}
} // namespace asteroids