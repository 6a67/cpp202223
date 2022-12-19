/*
 * BitmapReader.hpp
 *
 *  @date 09.12.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */


#ifndef BITMAPREADER_HPP_
#define BITMAPREADER_HPP_

namespace asteroids
{

class BitmapReader
{
public:

	/***
	 * @brief Constructor
	 */
	BitmapReader() : m_pixels(nullptr), m_width(0), m_height(0) {};

	/***
	 * @brief Destructor
	 */
	virtual ~BitmapReader() {};

	/***
	 * @brief Returns the bitmaps pixel array. Three bytes per pixel in RGB order
	 */
	virtual unsigned char* getPixels() { return m_pixels;}

	/***
	 * @brief Returns the width of the image.
	 */
	virtual int getWidth() { return m_width;}

	/***
	 * @brief Returns the height of the image
	 */
	virtual int getHeight() { return m_height;}

protected:

	/// Pixel array
	unsigned char*			m_pixels;

	/// Image width
	int						m_width;

	/// Image height
	int 					m_height;
};

} /* namespace asteroids */

#endif /* BITMAPREADER_HPP_ */
