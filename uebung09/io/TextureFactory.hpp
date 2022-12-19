#ifndef TEXTUREFACTORY_HPP
#define TEXTUREFACTORY_HPP

#include <string>
#include <map>
#include "rendering/Texture.hpp"

namespace asteroids
{

class TextureFactory
{
public:
    /**
     * @brief   Get the singleton instance of the factory
     *
     * @return  The instance
     */
    static TextureFactory& getInstance()
    {
        static TextureFactory instance;
        return instance;
    }

    /**
     * @brief   Set the base path in which textures are searched
     *
     * @param   base    The base path
     */
    void setBasePath(const std::string& base) noexcept(false);

    /**
     * @brief   Get a texture by its filename
     *
     * @param   filename    The filename
     * @return  The texture
     */
    Texture* getTexture(const std::string& filename) noexcept(false);

private:
    // Overload functions and make then private to prevent usage of them outside of the class
    TextureFactory() {}
    TextureFactory(const TextureFactory&);
    TextureFactory& operator=(const TextureFactory&);

    std::string                     m_basePath;
    std::map<std::string, Texture*> m_textures;
};

}  // namespace asteroids

#endif  // TEXTUREFACTORY_HPP