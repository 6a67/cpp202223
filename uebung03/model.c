/*
 *  model.c
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "model.h"
#include <stdio.h>

void printModel(Model* model)
{
    if(model)
    {
        printf("Number of vertices: %d\n", model->numVertices);
        printf("Number of faces: %d\n", model->numFaces);
    }
}

void printBuffers(Model* model)
{
    int i;
    if(model)
    {
        for(i = 0; i < model->numVertices; i++)
        {
            printf("F: %f %f %f\n", model->vertexBuffer[3 * i],
                                    model->vertexBuffer[3 * i + 1],
                                    model->vertexBuffer[3 * i + 2]);
        }

        for(i = 0; i < model->numFaces; i++)
        {
            printf("F: %d %d %d\n", model->indexBuffer[3 * i],
                                    model->indexBuffer[3 * i + 1],
                                    model->indexBuffer[3 * i + 2]);
        }
    }
}