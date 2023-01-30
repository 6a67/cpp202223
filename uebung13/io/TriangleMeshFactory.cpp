/*
 * TraingleMeshFactory.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */
#include <iostream>
using std::cout;
using std::endl;

#include "TriangleMeshFactory.hpp"

namespace asteroids
{

auto TriangleMeshFactory::getMesh(const string &meshName) -> TriangleMesh::Ptr
{
    // A mesh pointer
    TriangleMesh::Ptr mesh = nullptr;

    ///////////////////////////////////////////////////////////////////
    /// TODO: Use mesh loader feature to get mesh from HDF5 file
    ///////////////////////////////////////////////////////////////////

    return mesh;
}

TriangleMeshFactory& TriangleMeshFactory::instance()
{
    // Just crate on instance
    static TriangleMeshFactory instance;
    return instance;
}

///////////////////////////////////////////////////////////////////
/// TODO: Uncomment to use typedef from LevelParser as required
///////////////////////////////////////////////////////////////////

// void TriangleMeshFactory::setHdf5IO(const LevelParser::LevelHdf5IO &hdf5IO)
// {
//     m_Hdf5IO = hdf5IO;
// }

}
