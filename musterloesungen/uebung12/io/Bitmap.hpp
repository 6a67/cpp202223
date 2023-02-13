/*
 * Bitmap.hpp
 *
 *  @date 09.12.2018
 *  @author Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */


#ifndef Bitmap_HPP_
#define Bitmap_HPP_

#include <utility>

#include "util/SharedArray.hpp"

namespace asteroids
{

class Bitmap
{
public:

	using Ptr = shared_array<unsigned char>;

	/***
	 * @brief Constructor
	 */
	Bitmap() : m_pixels(nullptr), m_width(0), m_height(0), m_depth(0) {};

    Bitmap(Ptr pixels, int width, int height, int depth) : m_pixels(std::move(pixels)), m_width(width), m_height(height), m_depth(depth) {};

	/***
	 * @brief Destructor
	 */
	virtual ~Bitmap() {};

	/***
	 * @brief Returns the bitmaps pixel array. Three bytes per pixel in RGB order
	 */
	virtual Ptr getPixels() { return m_pixels;}

	/***
	 * @brief Returns the width of the image.
	 */
	virtual int getWidth() { return m_width;}

	/***
	 * @brief Returns the height of the image
	 */
	virtual int getHeight() { return m_height;}

    /***
     * @brief Returns the depth of the image
     */
    virtual int getDepth() { return m_depth;}

protected:

	/// Pixel array
	Ptr						m_pixels;

	/// Image width
	int						m_width;

	/// Image height
	int 					m_height;

    /// Image depth
	int 					m_depth;
};

} /* namespace asteroids */

#endif /* Bitmap_HPP_ */
