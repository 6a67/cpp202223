#ifndef IO_MODELIO_HPP
#define IO_MODELIO_HPP

#include "io/BaseHdf5IO.hpp"
#include "rendering/TexturedMesh.hpp"

namespace asteroids
{

namespace hdf5features
{

template<typename Derived>
class ModelIO
{
public:
    /**
     * @brief loads a tileset from hdf5
     *
     * hands over ownership of returned Tiles object!
     *
     * @tparam Tiles type of tileset (must support TileSetRepresentations constructor)
     * @param groupName name of group to load from
     * @param datasetName name of dataset that holds the tiles
     * @param tileW width of one tile
     * @param tileH height of one tile
     *
     * @return Tiles object that contains the tiles
     */
    template<typename Mesh>
    Mesh load(std::string groupName, std::string datasetName);

    /**
     * @brief loads a tileset from hdf5
     *
     * hands over ownership of returned Tiles object!
     *
     * @tparam Tiles type of tileset (must support TileSetRepresentations constructor)
     * @param group group to load from
     * @param datasetName name of dataset that holds the tiles
     * @param tileW width of one tile
     * @param tileH height of one tile
     *
     * @return Tiles object that contains the tiles
     */
    template<typename Mesh>
    Mesh load(HighFive::Group group);

    /**
     * @brief saves a TexturedMesh into hdf5
     *
     * @param groupName name of hdf5 group
     * @param datasetName name of hdf5 dataset
     * @param mesh mesh to write
     */
    void save(std::string groupName, std::string datasetName, TexturedMesh* mesh);

    /**
     * @brief saves a TexturedMesh into hdf5
     *
     * @param group hdf5 group
     * @param datasetName name of hdf5 dataset
     * @param mesh mesh to write
     */
    void save(HighFive::Group group, std::string datasetName, TexturedMesh* mesh);

    /**
     * @brief loads an Mesh from file and saves it into hdf5
     *
     * @param groupName name of group to save to
     * @param datasetName name of dataset to save to
     * @param meshFileName name of mesh file
     */
    void saveMesh(std::string groupName, std::string datasetName, const std::string& meshFileName);

private:
    Derived* m_fileAccess = static_cast<Derived*>(this);
};
} // namespace hdf5features

} // namespace asteroids

#include "ModelIO.tcc"

#endif

