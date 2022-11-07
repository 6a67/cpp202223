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

#ifndef __PLYIO_HPP__
#define __PLYIO_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model.h"

/**
 * @brief Loads a ply-File and creates vertex and index buffer arrays.
 *
 * @param file 		The name of the ply-File.
 * @param model		A pointer to model struct that will contain a 
 * 					representation of the loaded file if parsing 
 * 					was successful.
 */
 void loadply(
		char* file, Model* model);

#endif
