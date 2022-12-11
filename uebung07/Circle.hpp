//
// Created by sascha on 10.12.22.
//

#ifndef CPP18_ASTEROIDS_CIRCLE_HPP
#define CPP18_ASTEROIDS_CIRCLE_HPP


#include "Renderable2D.hpp"

namespace asteroids
{
class Circle : public Renderable2D
{
public:
    /**
     * @brief               Constructor
     * 
     * @param x             X position
     * @param y             Y position
     * @param radius        Radius
     * @param segments      Number of segments
    */
    Circle(MainWindow* mainWindow, float x, float y, float radius, int segments);

    /// Renders the circle
    void render() override;

private:
    /// Radius
    float m_radius;

    /// Number of segments
    int m_segments;
};
} // namespace asteroids

#endif //CPP18_ASTEROIDS_CIRCLE_HPP
