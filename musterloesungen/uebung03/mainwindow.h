/*
 *  mainwindow.h
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

/* OpenGL / glew Headers */
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

/* SDL2 Headers */
#include <SDL2/SDL.h>

#include "model.h"
/**
 * @brief   Creates an SDL window with OpenGL context
 * 
 * @param mainWindow    A pointer to SDL_Window*. After successful 
 *                      initialization, this pointer will contain
 *                      an intialized SDL_Window
 * @param mainContext   The SDL_GLContext that is associated with 
 *                      the given SDL_Window
 * @return int 
 */
int createSDLWindow(SDL_Window** mainWindow, SDL_GLContext* mainContext);

/**
 * @brief   The main loop that renders the game's contends to the 
 *          given SDL_Window
 * 
 * @param   mainWindow  A SDL_Window with OpenGL context to render
 *                      the game
 */
void mainLoop(SDL_Window* mainWindow, Model* model);


/**
 * @brief   Frees all used SDL resources
 * 
 * @param mainWindow    The main window to destroy
 * @param mainContext   The main window's OpenGL rendering context
 */
void cleanupSDL(SDL_Window* mainWindow, SDL_GLContext* mainContext);

/**
 * @brief   Prints the error descriptions and the line
 *          in which an SDL error occurred
 */
void printSDLError(int line);

#endif
