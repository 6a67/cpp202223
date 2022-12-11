#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Renderable2D.hpp"

namespace asteroids
{

class Circle : public Renderable2D
{
public:
    Circle(MainWindow* mainWindow, float x, float y, float radius, int segments);

    void render();

private:
    // Radius
    float m_radius;

    // Number of segments
    int m_segments;

};

}  // namespace asteroids
#endif // CIRCLE_HPP