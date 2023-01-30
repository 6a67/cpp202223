/*
 *  Circle.hpp
 *
 *  Created on: Nov. 24 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__

#include "math/Vector.hpp"
#include "Renderable2D.hpp"

#include <memory>

namespace asteroids
{
/**
 * @brief A class to render a cicle to the screen
 * 
 */
class Circle: public Renderable2D 
{
public:

    using Ptr = std::shared_ptr<Circle>;

    /**
     * @brief   Construct a new Circle object at the given center with the 
     *          specified radius
     * 
     * @param mainWindow    A pointer to a main window that renders the circle
     * @param center        The circle's center in screen coordinates
     * @param radius        radius
     * @param segments      Number of line segments to approximate the circle
     */
    Circle(MainWindow::Ptr mainWindow, const Vector2i& center, int radius, int segments = 10) :
        Renderable2D(mainWindow), m_center(center), m_r(radius), m_segments(segments) {}

    /**
     * @brief   Renders the circle
     * 
     */
    void render() override;

private:

    Vector2i m_center;

    /// radius
    int m_r;

    /// number of line segments to render 
    int m_segments;
};

} // namespace asteroids

#endif