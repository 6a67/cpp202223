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
	 * @brief   Contructs a triangle mesh from given buffers
	 * @param indexBuffer indexbuffer
	 * @param vertexBuffer vertexbuffer
	 * @param numFaces number of faces
	 * @param numVertices number of vertices
	 */
	TriangleMesh(int* indexBuffer, float* vertexBuffer, float* normals, int numFaces, int numVertices);


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
	 * @brief   Sets the normal buffer of the mesh
	 *
	 * @param normals The new normal buffer
	 */
	void setNormalBuffer(float* normals) { m_normalBuffer = normals;}

    /**
     * @brief   Sets the vertex buffer of the mesh
     *
     * @param vertices  The new vertex buffer
     * @param n         The number of vertices in the mesh
     */
	void setVertexBuffer(float* vertices, int n)
	{
	    m_vertexBuffer = vertices;
	    m_numVertices = n;
	}

    /**
     * @brief   Sets the index buffer of the mesh
     *
     * @param faces     The new index buffer
     * @param n         The number of faces in the mesh
     */

	void setIndexBuffer(int* faces, int n)
	{
	    m_indexBuffer = faces;
	    m_numFaces = n;
	}

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

    /// Normalbuffer
    float*      m_normalBuffer;

    /// Indexbuffer
    int*        m_indexBuffer;

    
};

} // namespace asteroids

#endif
