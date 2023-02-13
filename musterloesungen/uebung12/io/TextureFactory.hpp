/*
 *  TextureFactory.hpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */
#ifndef TEXTUREFACTORY_H_
#define TEXTUREFACTORY_H_

#include <string>

using std::string;

#include <map>

#include "LevelParser.hpp"
#include "rendering/Texture.hpp"

namespace asteroids
{

class TextureFactory
{
protected:

    /**
     * @brief Constructor
     */
    TextureFactory();

    /**
     * @brief Destructor
     */
    virtual ~TextureFactory();

    static std::map<string, Texture::Ptr> m_loadedTextures;

public:

    /**
     * @brief   Returns a new texture if the file contains readable
     *          image data or a null point if the file couldn't be parsed
     */
    auto getTexture(const string& meshName) -> Texture::Ptr;

    /**
     * @brief Sets the HDF 5 file for loading Textures
     */
    void setHdf5IO(const LevelParser::LevelHdf5IO& hdf5IO);

    /**
     * @brief   Returns the singleton instance
     */
    static TextureFactory& instance();

    LevelParser::LevelHdf5IO m_Hdf5IO;
};
}
#endif /* TEXTUREFACTORY_H_ */
