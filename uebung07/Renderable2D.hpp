//
// Created by sascha on 10.12.22.
//

#ifndef CPP18_ASTEROIDS_RENDERABLE2D_HPP
#define CPP18_ASTEROIDS_RENDERABLE2D_HPP

#include "MainWindow.hpp"
#include "Renderable.hpp"

namespace asteroids
{
class Renderable2D : public Renderable
{
public:
    /// Constructor
    Renderable2D(MainWindow* mainWindow);

    /// Renders the object
    virtual void render() = 0;

    /// Sets the current rendering color
    void setColor(float r, float g, float b);

protected:
    void begin2DRender();

    void end2DRender();

    /// Position
    float m_x;
    float m_y;

private:
    /// Pointer to main window
    MainWindow* m_mainWindow;

    /// Current rendering color in RGB
    float m_red;
    float m_green;
    float m_blue;

    /// Previous color
    float m_previousColor[4];

    // Dimensions
    float m_width;
    float m_height;
};
} // namespace asteroids

#endif //CPP18_ASTEROIDS_RENDERABLE2D_HPP
