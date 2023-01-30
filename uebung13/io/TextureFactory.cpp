/*
 *  TextureFactory.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "TextureFactory.hpp"
#include "Bitmap.hpp"

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

namespace asteroids
{

std::map<string, Texture::Ptr> TextureFactory::m_loadedTextures;


TextureFactory& TextureFactory::instance()
{
    // Just create one instance
    static TextureFactory instance;
    return instance;
}


///////////////////////////////////////////////////////////////////
/// TODO: Uncomment 
///////////////////////////////////////////////////////////////////

// void TextureFactory::setHdf5IO(const LevelParser::LevelHdf5IO& hdf5IO)
// {
//     m_Hdf5IO = hdf5IO;
// }

auto TextureFactory::getTexture(const string& filename) -> Texture::Ptr
{
    // A texture object
    Texture::Ptr tex = nullptr;

    auto it = m_loadedTextures.find(filename);
    if (it == m_loadedTextures.end())
    {
       ///////////////////////////////////////////////////////////////////
       /// TODO: Use your Texture-IO feature from the HDF5IO to load
       ///       a new texture from the HDF5 file 
       ///////////////////////////////////////////////////////////////////
        return tex;
    }
    else
    {
        return m_loadedTextures[filename];
    }
}
}

