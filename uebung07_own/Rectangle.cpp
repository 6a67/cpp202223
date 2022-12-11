#include "Rectangle.hpp"

namespace asteroids
{

Rectangle::Rectangle(MainWindow *window, float x, float y, float w, float h):
        Renderable2D(window)
{
    m_x = x;
    m_y = y;
    m_w = w;
    m_h = h;    
}
    

void Rectangle::render()
{
    Renderable2D::begin2DRender();
    glBegin(GL_LINE_LOOP);
    glVertex2d(m_x, m_y);
    glVertex2d(m_x + m_w, m_y);
    glVertex2d(m_x + m_w, m_y + m_h);
    glVertex2d(m_x, m_y + m_h);
    glEnd();
    Renderable2D::end2DRender();
}


}  // namespace asteroids