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
    // Determine file extension
    string ext = GetExtensionFromFileName(filename);

    // Transform to lower case
    transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

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

    TriangleMesh* mesh = nullptr;
    mesh               = meshReader->getMesh();
    delete meshReader;

    return mesh;
}
}  // namespace asteroids