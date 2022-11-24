/*
 *  MainWindow.hpp
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__

#include <string>

#include <SDL2/SDL.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include "Model.hpp"

#include "Camera.hpp"

namespace asteroids
{

class MainWindow
{
public:
    /**
     * @brief Construct a new Main Window object
     *
     * @param title    The title of the window
     * @param plyname  A .ply file to render
     * @param w        The window width
     * @param h        The window heigt
     */
    MainWindow(const std::string& title, const std::string& plyname, int w, int h);

    /**
     * @brief Start the window's main loop
     */
    void execute();

    /**
     * @brief Destroys the Main Window object
     *
     */
    ~MainWindow();

    // TODO: ADD NEEDED DATA MEMBERS


private:
    /* Our SDL_Window ( just like with SDL2 wihout OpenGL) */
    SDL_Window* m_sdlMainWindow;

    /* Our opengl context handle */
    SDL_GLContext m_mainContext;

    /* The model to render */
    Model* m_model;

    /* Camera that can move */
    asteroids::Camera m_camera;


};

}

#endif
