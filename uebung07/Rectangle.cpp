//
// Created by sascha on 10.12.22.
//
#include "Rectangle.hpp"

namespace asteroids
{
Rectangle::Rectangle(asteroids::MainWindow* mainWindow, float x, float y, float w, float h) : Renderable2D(mainWindow)
{
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;
}

/**
 * @brief renderRectangle   Renders a rectangle
 * @param m_x               X coordinate of upper left corner
 * @param m_y               Y coordinate of upper left corner
 * @param m_w               Width
 * @param m_h               Height
 */
void Rectangle::render()
{
    begin2DRender();

    glBegin(GL_LINE_LOOP);
    glVertex2d(m_x, m_y);
    glVertex2d(m_x + m_w, m_y);
    glVertex2d(m_x + m_w, m_y + m_h);
    glVertex2d(m_x, m_y + m_h);
    glEnd();

    end2DRender();
}
} // namespace asteroids