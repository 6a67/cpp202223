/*
 *  MainWindow.cpp
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "MainWindow.hpp"

#include <iostream>


namespace asteroids
{


MainWindow::MainWindow(const std::string& title, const std::string& plyname, int w, int h):
m_camera({0, 0, -750}, 0.01, 1)
{
    /* Initialize SDL's Video subsystem */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to init SDL" << std::endl;
    }

    /* Create our window centered at 512x512 resolution */
    m_sdlMainWindow = SDL_CreateWindow(
        title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);

    /* Check that everything worked out okay */
    if (!m_sdlMainWindow)
    {
        std::cout << "Unable to create window" << std::endl;
    }

    /* Create our opengl context and attach it to our window */
    m_mainContext = SDL_GL_CreateContext(m_sdlMainWindow);

    /* Check that everything worked out okay */
    if (!m_mainContext)
    {
        std::cout << "Unable to create OpenGL context" << std::endl;
    }

    /* Set our OpenGL version.
       SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    /* 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
     */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    /* Turn on double buffering with a 24bit Z buffer.
       You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);

/* Init GLEW */
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    glewInit();
#endif


    SDL_GL_SwapWindow(m_sdlMainWindow);

    /* Init OpenGL projection matrix */
    glClearColor(0.0, 0.0, 0.0, 1.0);
    float ratio = 1024 * 1.0 / 768;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, 1027, 768);
    gluPerspective(45, ratio, 1, 10000);

    /* Ender model view mode */

    glMatrixMode(GL_MODELVIEW);


    /* Init model */
    m_model = new Model(plyname);
}

void MainWindow::execute()
{
    bool loop = true;

    /* Set camera position and direction */
    glLoadIdentity();
    gluLookAt(0.0, 0.0, -750.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

    while (loop)
    {
        /* Check for events */
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    loop = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_w:
                            m_camera.move(Camera::FORWARD);
                            break;
                        case SDLK_s:
                            m_camera.move(Camera::BACKWARD);
                            break;
                        case SDLK_a:
                            m_camera.turn(Camera::LEFT);
                            break;
                        case SDLK_d:
                            m_camera.turn(Camera::RIGHT);
                            break;
                        case SDLK_q:
                            m_camera.turn(Camera::UP);
                            break;
                        case SDLK_e:
                            m_camera.turn(Camera::DOWN);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }

        }
        
        m_camera.apply();

        glClear(GL_COLOR_BUFFER_BIT);

        /* Render model */
        m_model->render();

        /* Bring up back buffer */
        SDL_GL_SwapWindow(m_sdlMainWindow);

    }


    // TODO: IMPLEMENT MAIN LOOP HERE
    // FIRST IMPLEMENT BASIC FUNCTIONALITY BASED
    // ON THE PROVIDED SOLUTION OF THE 3rd ASSGINMENT.
    // AFTER THIS PORT IS DONE, ADD CAMERA HANDLING
    // AS REQUESTED IN THE SECOND EXERCISE.
}

MainWindow::~MainWindow()
{
    /* Clean up model */
    if (m_model)
    {
        delete m_model;
    }

    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(m_mainContext);
    SDL_DestroyWindow(m_sdlMainWindow);
    SDL_Quit();
}


}  // namespace asteroids
