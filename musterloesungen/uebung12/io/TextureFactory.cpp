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

#include "ModelIO.hpp"
#include "TextureFactory.hpp"
#include "Bitmap.hpp"
#include "TextureIO.hpp"

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

namespace asteroids
{

std::map<string, Texture::Ptr> TextureFactory::m_loadedTextures;

TextureFactory::TextureFactory()
{
    // TODO Auto-generated constructor stub

}

TextureFactory::~TextureFactory()
{
    // TODO Auto-generated destructor stub
}

TextureFactory& TextureFactory::instance()
{
    // Just create one instance
    static TextureFactory instance;
    return instance;
}

void TextureFactory::setHdf5IO(const LevelParser::LevelHdf5IO& hdf5IO)
{
    m_Hdf5IO = hdf5IO;
}

auto TextureFactory::getTexture(const string& filename) -> Texture::Ptr
{
    // A texture object
    Texture::Ptr tex = nullptr;

    auto it = m_loadedTextures.find(filename);
    if (it == m_loadedTextures.end())
    {
        Bitmap bitmap = m_Hdf5IO.TextureIO::load("textures", filename);
        if (bitmap.getDepth() == 3)
        {
            tex = std::make_shared<Texture>(bitmap.getPixels(), bitmap.getWidth(), bitmap.getHeight(), filename);
            m_loadedTextures[filename] = tex;
        }
        else
        {
            std::cout << "Only pictures with RGB values are supported!" << std::endl;
        }

        return tex;
    }
    else
    {
        return m_loadedTextures[filename];
    }
}
}

