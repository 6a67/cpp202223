/**
 * MeshIO.h
 *
 *  @date 10.12.2011
 *  @author Thomas Wiemann
 */

#ifndef MESHIO_H_
#define MESHIO_H_

#include "rendering/TriangleMesh.hpp"

namespace asteroids
{

/**
 * @brief Base class for Mesh in- and output
 */
class MeshReader
{
public:
    MeshReader()
        : m_vertexBuffer(0),  // Initit all members with zero pointers
          m_normalBuffer(0),
          m_indexBuffer(0),
          m_numVertices(0),
          m_numFaces(0) {};


    /**
     * @brief Destructor. Nothing to do right now
     */
    virtual ~MeshReader() {};

    /**
     * @brief Returns a pointer to a triangle mesh instance
     */
    virtual TriangleMesh* getMesh() = 0;

protected:

    /// Vertex position information
    float*  m_vertexBuffer;

    /// Vertex normal information
    float*  m_normalBuffer;

    /// Triangle definitions
    int*    m_indexBuffer;

    /// Number of vertices in mesh
    int     m_numVertices;

    /// Number of faces in mesh
    int     m_numFaces;
};

}

#endif /* MESHIO_H_ */
