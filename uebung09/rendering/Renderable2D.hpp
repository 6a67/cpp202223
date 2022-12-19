/*
 *  Renderable2D.hpp
 *
 *  Created on: Nov. 24 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __RENDERABLE2D_HPP__
#define __RENDERABLE2D_HPP__

#include "Renderable.hpp"


namespace asteroids
{
class MainWindow;

/**
 * @brief   A class to represent objects that are rendered
 *          in screen space
 * 
 */
class Renderable2D : public Renderable
{
    // Makes default constructor inaccessible...
    Renderable2D() {}
public:

    /// Constructor
    Renderable2D(MainWindow* mainWindow) : 
        m_r(1.0), m_g(1.0), m_b(1.0), 
        m_mainWindow(mainWindow) {}

    /// Renders the object
    virtual void render() = 0;

    /// Sets the current rendering color
    void setColor(float r, float g, float b);

protected:

    /// Enters 2D rendering mode
    void begin2D();

    /// Leaves 2D rendering mode
    void end2D();

    /// Red component of rendering color
    float m_r;

    /// Green component of rendering color
    float m_g;

    /// Blue component of rendering color
    float m_b;

    /// Pointer to a main window instance that displays
    /// this renderable
    MainWindow* m_mainWindow;
};


} // namespace asteroids
#endif