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

#include "view/Camera.hpp"
#include "rendering/SpaceCraft.hpp"
#include "rendering/Skybox.hpp"
#include "rendering/AsteroidField.hpp"

namespace asteroids
{
/**
 * @brief   Represents the main window of the game. This
 *          class contains the main loop, handles all
 *          user input and renders all objects
 * 
 */
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

    /// Returns the width of the window
    int width();

    /// Returns the height of the windows
    int height();
    
private:

    /// A pointer to the Actor
    SpaceCraft*     m_ship;

    /// The virtual camera
    Camera          m_camera;  

	/// A skybox for the scene
	Skybox*         m_skybox;

    /// An AsteroidField
	AsteroidField*  m_asteroidField;

    /// The window width
    int             m_width;

    /// The window height
    int             m_height;

    /// The SDL Window
    SDL_Window*     m_sdlWindow;

    /// The SDL OpenGL rendering context
    SDL_GLContext   m_sdlGlcontext;
};

}

#endif
