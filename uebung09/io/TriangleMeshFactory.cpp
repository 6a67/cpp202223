#include "io/TriangleMeshFactory.hpp"
#include "util/Util.hpp"
#include "io/MeshReader.hpp"
#include "io/Read3DS.hpp"
#include "io/ReadPLY.hpp"
#include <algorithm>

namespace asteroids
{

void TriangleMeshFactory::setBasePath(const string& base) noexcept(false)
{
    m_basePath = validatePath(base);
}

TriangleMesh* TriangleMeshFactory::getMesh(const string& filename) const noexcept(false)
{
    // Check if mesh is already loaded
    // if (m_meshes.find(filename) != m_meshes.end())
    // {
    //     return m_meshes.at(filename);
    // }

    // Determine file extension
    string ext = GetExtensionFromFileName(filename);

    // Transform to lower case
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    // File path for mesh
    string filePath = m_basePath + filename;

    // The factory function to determine the correct loader
    MeshReader* meshReader = nullptr;

    if (ext == "3ds")
    {
        meshReader = new Read3DS(filePath);
    }
    else if (ext == "ply")
    {
        meshReader = new ReadPLY(filePath);
    }
    else
    {
        throw runtime_error("Unknown file extension: " + ext);
    }

    TriangleMesh* mesh = meshReader->getMesh();
    delete meshReader;
    // m_meshes[filename] = mesh;
    return mesh;
}

TriangleMeshFactory::~TriangleMeshFactory()
{
    // for (auto& mesh : m_meshes)
    // {
    //     delete mesh.second;
    // }

    // m_meshes.clear();
}

}  // namespace asteroids