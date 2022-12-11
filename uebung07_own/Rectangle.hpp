#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Renderable2D.hpp"

namespace asteroids
{
    
class Rectangle : public Renderable2D
{
public:

    Rectangle(MainWindow* window, float x, float y, float w, float h);

    void render();

private:
    // Dimensions
    float m_w;
    float m_h;

};



}  // namespace asteroids
#endif // RECTANGLE_HPP