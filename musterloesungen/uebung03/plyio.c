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

void loadply(char *file, Model *model)
{
	int header_read = 0;
	char line[100];
	int v_count;
	int f_count;

	char *token;

	int i;

	if (model)
	{

		FILE *ply_file = fopen(file, "r");

		if (ply_file == NULL)
		{
			model->vertexBuffer = 0;
			model->indexBuffer = 0;
			model->numVertices = 0;
			model->numFaces = 0;
			perror("Unable to open file: ");
			return;
		}

		/* Read Header */
		fgets(line, sizeof(line), ply_file);

		if (strcmp(line, "ply\n") != 0)
		{
			model->vertexBuffer = 0;
			model->indexBuffer = 0;
			model->numVertices = 0;
			model->numFaces = 0;
			perror("This is not a .ply file: ");
			return;
		}
		printf("Reading header ... \n");

		while (!header_read)
		{
			fgets(line, sizeof(line), ply_file);
			token = strtok(line, " ");

			if (strcmp(token, "comment") == 0)
			{
				continue;
			}

			/* End Header */
			if (strcmp(token, "end_header\n") == 0)
			{
				header_read = 1;
				break;
			}

			/* Parse element */
			if (strcmp(token, "element") == 0)
			{
				token = strtok(NULL, " ");

				/* Parse vertex */
				if (strcmp(token, "vertex") == 0)
				{
					token = strtok(NULL, " ");
					v_count = atoi(token);
					printf("%d\n", v_count);
					model->numVertices = v_count;
					model->vertexBuffer = (float *)calloc(v_count * 3, sizeof(float));
				}

				/* parse face */
				if (strcmp(token, "face") == 0)
				{
					token = strtok(NULL, " ");
					f_count = atoi(token);
					model->numFaces = f_count;
					model->indexBuffer = (int *)calloc(f_count * 3, sizeof(int));
				}
			}
		}

		fread(model->vertexBuffer, sizeof(float), 3 * v_count, ply_file);

		for (int i = 0; i < model->numFaces; i++)
		{
			unsigned char dummy;
			fread(&dummy, sizeof(unsigned char), 1, ply_file);
			fread(&model->indexBuffer[3 * i], sizeof(int), 3, ply_file);
		}

		// for(int i = 0; i < model->numVertices; i++)
		// {
		// 	printf("%f %f %f\n", model->vertexBuffer[3 * i], model->vertexBuffer[3 * i + 1], model->vertexBuffer[3 * i + 2]);
		// }

		// for(int i = 0; i < model->numFaces; i++)
		// {
		// 	printf("%d %d %d\n", model->indexBuffer[3 * i], model->indexBuffer[3 * i + 1], model->indexBuffer[3 * i + 2]);
		// }

		/* /\* Write Vertices *\/ */
		/* for (i = 0; i < v_count; i++) { */
		/* 	fgets(line, sizeof(line), ply_file); */
		/* 	write_vertices_to_buffer(line, v_buffer); */
		/* 	v_buffer+=3; */
		/* } */

		/* /\* Write Index *\/ */
		/* for (i = 0; i < f_count; i++) { */
		/* 	fgets(line, sizeof(line), ply_file); */
		/* 	write_indices_to_buffer(line, f_buffer); */
		/* 	f_buffer += 3; */
		/* } */

		/* Load vertices */
		fclose(ply_file);
	}
}
