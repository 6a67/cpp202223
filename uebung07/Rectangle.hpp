//
// Created by sascha on 10.12.22.
//

#ifndef CPP18_ASTEROIDS_RECTANGLE_HPP
#define CPP18_ASTEROIDS_RECTANGLE_HPP

#include "Renderable2D.hpp"

namespace asteroids
{
class Rectangle : public Renderable2D
{
public:
    Rectangle(MainWindow* mainWindow, float x, float y, float w, float h);

    void render() override;

private:
    float m_w;
    float m_h;
};
} // namespace asteroids

#endif //CPP18_ASTEROIDS_RECTANGLE_HPP
