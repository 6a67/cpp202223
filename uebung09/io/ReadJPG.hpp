/**
 * ReadJPG.hpp
 *
 *  @date 30.11.2014
 *  @author Thomas Wiemann
 */

#ifndef READJPG_HPP_
#define READJPG_HPP_

#include <iostream>
#include <fstream>

#include <jpeglib.h>
#include <jerror.h>

#include <string>
using std::string;

#include "BitmapReader.hpp"

namespace asteroids
{

class ReadJPG : public BitmapReader
{
public:

	/**
	 * @brief Constructor
	 */
    ReadJPG(string filename);

    /**
     * @brief Destruktor
     */
    ~ReadJPG();

};

}






#endif /* READJPG_HPP_ */
