/*
 *  Rectangle.hpp
 *
 *  Created on: Nov. 24 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __RECTANGLE_HPP__
#define __RECTANGLE_HPP__

#include "math/Vector.hpp"
#include "Renderable2D.hpp"

#include <memory>

namespace asteroids
{
/**
 * @brief Draws an rectangle to the screen
 * 
 */
class Rectangle : public Renderable2D 
{
public:

    using Ptr = std::shared_ptr<Rectangle>;

    /**
     * @brief   Construct a new Rectangle object. The rectangle
     *          is defined by the top left position and corresponding
     *          with and height
     * 
     * @param mainWindow    A main window that holds the rectangle
     * @param position      Position of the top left corner
     * @param dimension     Width and height of the rectangle
     */
    Rectangle(
        MainWindow::Ptr mainWindow,
        const Vector2i& position, 
        const Vector2i& dimension) : 
            Renderable2D(mainWindow), 
            m_position(position), 
            m_dimension(dimension) { }
    /**
     * @brief   Renders the rectangle
     * 
     */
    void render() override;

private:

    /// Position of the rectangle
    Vector2i    m_position;

    /// Dimensions of the rectangle
    Vector2i    m_dimension;

};

} // namespace asteroids
#endif
