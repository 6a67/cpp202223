/*
 *  plyio.c
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "plyio.h"

void returnError(Model* model)
{
    model->numFaces     = 0;
    model->numVertices  = 0;
    model->indexBuffer  = NULL;
    model->vertexBuffer = NULL;
}


void loadply(char* file, Model* model)
{
    /* Load PLY model from model/arrow.ply */
    FILE* pFile = fopen(file, "r");
    if (pFile == NULL)
    {
        printf("Could not open file\n");
        returnError(model);
        return;
    }

    /* Read model data */

    /* Read file line by line with fread() */
    char line[1024];
    int  lineCount = 0;
    while (fgets(line, 1024, pFile) != NULL)
    {
        lineCount++;
        if (strncmp(line, "element face", 12) == 0)
        {
            sscanf(line, "element face %d", &model->numFaces);
        }
        else if (strncmp(line, "element vertex", 14) == 0)
        {
            sscanf(line, "element vertex %d", &model->numVertices);
        }
        else if (strncmp(line, "end_header", 10) == 0)
        {
            break;
        }
    }

    /* Allocate memory for vertex and index buffer */
    model->indexBuffer  = (int*) malloc(4 * model->numFaces * sizeof(int));
    model->vertexBuffer = (float*) malloc(3 * model->numVertices * sizeof(float));

    if (fread(model->vertexBuffer, sizeof(float), 3 * model->numVertices, pFile)
        != 3 * model->numVertices)
    {
        printf("Could not read vertices\n");
        returnError(model);
        return;
    }

    for (int i = 0; i < model->numFaces; i++)
    {
        /* Skip the uchar as we was told that we can expect it always to be 3 */
        if (fseek(pFile, 1, SEEK_CUR) != 0)
        {
            printf("Could not read index buffer\n");
            returnError(model);
            return;
        }

        if (fread(model->indexBuffer + 3 * i, sizeof(int), 3, pFile) != 3)
        {
            printf("Could not read face\n");
            returnError(model);
            return;
        }
    }

    /* Close file */
    if (fclose(pFile) == EOF)
    {
        printf("Could not close file\n");
        returnError(model);
        return;
    }
}
