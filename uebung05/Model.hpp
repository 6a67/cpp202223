/*
 *  Model.hpp
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <string>

namespace asteroids
{
    

/**
 * @brief A struct to represent a simple 3D model 
 * 
 */
class Model
{
public:
    /**
     * @brief Construct a new Model object from the given PLY file
     * 
     * @param filename      A .ply file containing the model definition
     */
    Model(const std::string& filename);

    /**
     * @brief Prints general information (number of vertices and faces) 
     *        to stdout.
     * 
     */
    void printModelInformation();

    /**
     * @brief Prints the contends of the internal buffers to stdout.
     * 
     */
    void printBuffers();

    /**
     * @brief Renders the model
     * 
     */
    void render();

    /**
     * @brief Destroys the Model object
     * 
     */
    ~Model();

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
