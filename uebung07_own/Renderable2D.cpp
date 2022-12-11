#include "Renderable2D.hpp"

namespace asteroids
{

Renderable2D::Renderable2D(MainWindow *mainWindow): m_mainWindow(mainWindow) {}

void Renderable2D::begin2DRender() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, m_mainWindow->width(), m_mainWindow->height(), 0.0f, -10.0f, 10.0f);

    // get the current color
    glGetFloatv(GL_CURRENT_COLOR, m_oldColor);

    // set color
    glColor3f(m_r, m_g, m_b);
}

void Renderable2D::end2DRender() {   
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // reset color
    glColor3f(m_oldColor[0], m_oldColor[1], m_oldColor[2]);
}


void Renderable2D::setColor(float r, float g, float b) {
    m_r = r;
    m_g = g;
    m_b = b;
}


} // namespace asteroids