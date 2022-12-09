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

MainWindow::MainWindow(
    const std::string& title, 
    const std::string& plyname, int w, int h)
    : m_camera(Vector(0.0f, 0.0f, -700.0f), 0.05f, 5.0f) 
{
    // Save width and height
    m_height = h;
    m_width = w;

    // Setup window
    m_sdlWindow = SDL_CreateWindow(
        "SDL Main Window", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, SDL_WINDOW_OPENGL);

    if(!m_sdlWindow)
    {
        std::cout << "MainWindow: Unable to create SDL window" << std::endl;
    }

    m_sdlGlcontext = SDL_GL_CreateContext(m_sdlWindow);

    if(!m_sdlGlcontext)
    {
        std::cout << "MainWindow: Unable to creade SDL GL context" << std::endl;
    } 

    if(m_sdlWindow && m_sdlGlcontext)
    {
        // Set our OpenGL version.
	    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled 
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // 3.2 is part of the modern versions of OpenGL, 
        // but most video cards whould be able to run it 
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        // Turn on double buffering with a 24bit Z buffer.
	    // You may need to change this to 16 or 32 for your system 
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // This makes our buffer swap syncronized with the monitor's vertical refresh 
        SDL_GL_SetSwapInterval(1);

#ifndef __APPLE__
        glewExperimental = GL_TRUE;
        glewInit();
#endif
        SDL_GL_SwapWindow(m_sdlWindow);

        // Init OpenGL projection matrix 
        glClearColor(0.0, 0.0, 0.0, 1.0);
        float ratio = m_width * 1.0 / m_height;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, m_width, m_height);
        gluPerspective(45, ratio, 1, 10000);

        // Enter model view mode 
        glMatrixMode(GL_MODELVIEW);
    }

    // Load model
    m_model = new Model(plyname);
}

void MainWindow::execute()
{
    if(m_model && m_sdlWindow && m_sdlGlcontext)
    {
        bool loop = true;
        const Uint8* keyStates;
       
        while (loop)
        {
            // Clear background
            glClear(GL_COLOR_BUFFER_BIT );

            // Apply camera, also loads indentity matrix
            m_camera.apply();

            // Markers for mouse buttons
            bool r_pressed = false;
            bool l_pressed = false;

            // Handle events
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    // Window was closed, exit main loop
                    case SDL_QUIT:
                        loop = false;
                        break;
                    // Handle mouse motion
                    case SDL_MOUSEMOTION:

                            // Check if left button is pressed
                            if(event.motion.state & SDL_BUTTON_LMASK)
                            {
                                l_pressed = true;
                            }

                            // Check if right button is pressed
                            if(event.motion.state & SDL_BUTTON_RMASK)
                            {
                                r_pressed = true;
                            }

                            // Handle motion for pressed L button while R is not
                            // pressed 
                            if(l_pressed & !r_pressed)
                            {
                               if(event.motion.xrel > -3)
                                {
                                    m_camera.turn(Camera::LEFT);
                                }
                                if(event.motion.xrel < 3)
                                {
                                    m_camera.turn(Camera::RIGHT);
                                }
                                if(event.motion.yrel > 3)
                                {
                                    m_camera.turn(Camera::UP);
                                }
                                if(event.motion.yrel < -3)
                                {
                                    m_camera.turn(Camera::DOWN);
                                }
                            }

                            // Handle motion for pressed R button while L is not
                            // pressed 
                            if(r_pressed & !l_pressed)
                            {
                               if(event.motion.xrel > 3)
                               {
                                   m_camera.move(Camera::RIGHT);
                               }
                               if(event.motion.xrel < -3)
                               {
                                   m_camera.move(Camera::LEFT);
                               } if(event.motion.yrel > 3)
                               {
                                   m_camera.move(Camera::FORWARD);
                               }
                               if(event.motion.yrel < -3)
                               {
                                   m_camera.move(Camera::BACKWARD);
                               }
                            }
                        break;
                    default:
                        break;
                }

                // Get keyboard states and handle model movement
                keyStates = SDL_GetKeyboardState(NULL);

                if(keyStates[SDL_SCANCODE_UP])
                {
                    m_model->rotate(Model::YAW, 0.05);
                }
                if(keyStates[SDL_SCANCODE_DOWN])
                {
                    m_model->rotate(Model::YAW, -0.05);
                }
                if(keyStates[SDL_SCANCODE_LEFT])
                {
                    m_model->rotate(Model::ROLL, 0.05);
                }
                if(keyStates[SDL_SCANCODE_RIGHT])
                {
                    m_model->rotate(Model::ROLL, -0.05);
                }
                if(keyStates[SDL_SCANCODE_W])
                {
                    m_model->move(Model::ACCEL, 5);
                }
                if(keyStates[SDL_SCANCODE_S])
                {
                    m_model->move(Model::ACCEL, -5);
                }
                if(keyStates[SDL_SCANCODE_A])
                {
                    m_model->move(Model::STRAFE, 5);
                }
                if(keyStates[SDL_SCANCODE_D])
                {
                    m_model->move(Model::STRAFE, -5);
                }
            }

            // Render model
            m_model->render();

            // Bring up back buffer 
		    SDL_GL_SwapWindow(m_sdlWindow);
        }
    }
}

MainWindow::~MainWindow()
{
    // Delete model
    if(m_model)
    {
        delete m_model;
    }

    // Cleanup SDL stuff
	SDL_GL_DeleteContext(m_sdlGlcontext);

	// Destroy our window 
	SDL_DestroyWindow(m_sdlWindow);

	// Shutdown SDL 2 
	SDL_Quit();
}

} // namespace asteroids
