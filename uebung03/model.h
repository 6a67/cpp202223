/*
 *  model.h 
 * 
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __MODEL_H__
#define __MODEL_H__

/**
 * @brief A struct to represent a simple 3D model 
 * 
 */
typedef struct {
    /* Number of vertices */
    int     numVertices;

    /* Number of faces */
    int     numFaces;

    /* Vertex array consisting of (x,y,z) triples of vertex coordinates */
    float*  vertexBuffer;

    /* Index array referencing the vertices */
    int*    indexBuffer;
} Model;


/**
 * @brief   Prints information about the given \ref model to 
 *          stdout.
 */
void printModel(Model* model);

/**
 * @brief   Prints the contends of the index and vertex buffer
 *          of the given \ref model 
 */
void printBuffers(Model* model);

#endif