/*
 *  TriangleMesh.hpp
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __TriangleMesh_HPP__
#define __TriangleMesh_HPP__

#include <string>

#include "Renderable3D.hpp"

namespace asteroids
{
    

/**
 * @brief A struct to represent a simple 3D TriangleMesh 
 * 
 */
class TriangleMesh : public Renderable3D
{
public:

    TriangleMesh();

    /**
     * @brief Construct a new TriangleMesh object from another instance
     * 
     * @param other         Instance to clone
     */
    TriangleMesh(const TriangleMesh& other);

    /**
     * @brief Construct a new TriangleMesh object from the given PLY file
     * 
     * @param filename      A .ply file containing the TriangleMesh definition
     */
    TriangleMesh(const std::string& filename);

    /**
	 * @brief   Contructs a triangle mesh from given buffers
	 * @param indexBuffer indexbuffer
	 * @param vertexBuffer vertexbuffer
	 * @param numFaces number of faces
	 * @param numVertices number of vertices
	 */
	TriangleMesh(int* indexBuffer, float* vertexBuffer, int numFaces, int numVertices);


    /**
     * @brief Prints general information (number of vertices and faces) 
     *        to stdout.
     * 
     */
    void printTriangleMeshInformation();

    /**
     * @brief Prints the contends of the internal buffers to stdout.
     * 
     */
    void printBuffers();

    /**
     * @brief Renders the triangle mesh
     * 
     */
    virtual void render();

    /**
     * @brief Destroys the TriangleMesh object
     * 
     */
    virtual ~TriangleMesh();

protected:

    /// Number of vertices
    int         m_numVertices;

    /// Number of faces
    int         m_numFaces;

    /// Vertexbuffer
    float*      m_vertexBuffer;

    /// Indexbuffer
    int*        m_indexBuffer;

    
};

} // namespace asteroids

#endif
