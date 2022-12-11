#ifndef RENDERABLE2D_HPP
#define RENDERABLE2D_HPP

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

    // Position
    float m_x;
    float m_y;

private:
    // Pointer to the main window
    MainWindow* m_mainWindow;

    // Current rendering color
    float m_r;
    float m_g;
    float m_b;

    // Old color
    float m_oldColor[4];


};

} // namespace asteroids
#endif // RENDERABLE2D_HPP