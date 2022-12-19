#include "io/TextureFactory.hpp"
#include "io/BitmapReader.hpp"
#include "io/ReadTGA.hpp"
#include "io/ReadTIFF.hpp"
#include "io/ReadPPM.hpp"
#include "io/ReadJPG.hpp"
#include "util/Util.hpp"
#include <algorithm>

namespace asteroids
{

void TextureFactory::setBasePath(const string& base) noexcept(false)
{
    m_basePath = validatePath(base);
}

Texture* TextureFactory::getTexture(const std::string& filename) noexcept(false)
{
    // Check if texture is already loaded
    if (m_textures.find(filename) != m_textures.end())
    {
        return m_textures[filename];
    }

    // Determine file extension
    string ext = GetExtensionFromFileName(filename);

    // Transform to lower case
    transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    // File path for texture
    string filePath = m_basePath + filename;

    // The factory function to determine the correct loader
    BitmapReader* bmpReader;

    if (ext == "tga")
    {
        bmpReader = new ReadTGA(filePath);
    }
    else if (ext == "tif" || ext == "tiff")
    {
        bmpReader = new ReadTIFF(filePath);
    }
    else if (ext == "ppm")
    {
        bmpReader = new ReadPPM(filePath);
    }
    else if (ext == "jpg" || ext == "jpeg")
    {
        bmpReader = new ReadJPG(filePath);
    }
    else
    {
        throw std::runtime_error("Unsupported file format: " + ext);
    }
    Texture* texture
        = new Texture(bmpReader->getPixels(), bmpReader->getWidth(), bmpReader->getHeight());
    delete bmpReader;
    m_textures[filename] = texture;
    return texture;
}
}  // namespace asteroids