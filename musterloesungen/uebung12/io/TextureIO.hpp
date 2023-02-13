#ifndef IO_TEXTUREIO_HPP
#define IO_TEXTUREIO_HPP

#include <SDL.h>

#include "ReadPPM.hpp"
#include "ReadTGA.hpp"
#include "ReadJPG.hpp"

namespace asteroids
{

namespace hdf5features
{

template<typename Derived>
class TextureIO
{
public:
    /**
     * @brief loads an sdl surface from hdf5
     *
     * hands over ownership of returned sdl_surface!
     *
     * @param groupName name of group of image
     * @param datasetName name of hdf5 dataset that holds the image
     *
     * @return Sdl surface holding the loaded image
     */
    Bitmap load(std::string groupName, std::string datasetName);

    /**
     * @brief loads an sdl surface from hdf5
     *
     * hands over ownership of returned sdl_surface!
     *
     * @param group group of image
     * @param datasetName name of hdf5 dataset that holds the image
     *
     * @return Sdl surface holding the loaded image
     */
    Bitmap load(HighFive::Group group, std::string datasetName);

    /**
     * @brief saves an sdl surface to hdf5 file
     *
     * @param groupName nae of group in hdf5 to save to
     * @param datasetName name of dataset
     * @param texture sdl surface to write
     */
    void save(std::string groupName, std::string datasetName, Bitmap* texture);

    /**
     * @brief saves an sdl surface to hdf5 file
     *
     * @param group group in hdf5 to save to
     * @param datasetName name of dataset
     * @param texture sdl surface to write
     */
    void save(HighFive::Group group, std::string datasetName, Bitmap* texture);

    /**
     * @brief loads an image from file and saves it into hdf5
     *
     * @param groupName name of group to save to
     * @param datasetName name of dataset to save to
     * @param imageFileName name of image file
     */
    void saveImage(std::string groupName, std::string datasetName, const std::string& imageFileName);

private:
    Derived* m_fileAccess = static_cast<Derived*>(this);
};
} // namespace hdf5features

} // namespace asteroids

#include "TextureIO.tcc"

#endif
