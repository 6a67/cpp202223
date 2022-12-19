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
    const std::string& file, int w, int h)
    : m_camera(Vector3f(0.0f, 0.0f, -700.0f), 0.05f, 5.0f) 
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
        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

        // Setup two light sources
        float light0_position[4];
        float light0_ambient[4];
        float light0_diffuse[4];

        float light1_position[4];
        float light1_ambient[4];
        float light1_diffuse[4];

        light0_position[0] =   1.0f; light0_ambient[0] = 0.8f; light0_diffuse[0] = 0.8f;
        light0_position[1] =   1.0f; light0_ambient[1] = 0.8f; light0_diffuse[1] = 0.8f;
        light0_position[2] =   0.0f; light0_ambient[2] = 0.8f; light0_diffuse[2] = 0.8f;
        light0_position[3] =   1.0f; light0_ambient[3] = 0.1f; light0_diffuse[3] = 1.0f;

        light1_position[0] =   0.0f; light1_ambient[0] = 0.1f; light1_diffuse[0] = 0.5f;
        light1_position[1] =  -1.0f; light1_ambient[1] = 0.1f; light1_diffuse[1] = 0.5f;
        light1_position[2] =   0.0f; light1_ambient[2] = 0.1f; light1_diffuse[2] = 0.5f;
        light1_position[3] =   1.0f; light1_ambient[3] = 1.0f; light1_diffuse[3] = 1.0f;

        // Light 1
        glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
        glEnable(GL_LIGHT0);

        // Light 2
        glLightfv(GL_LIGHT1, GL_AMBIENT,  light1_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1_diffuse);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glEnable(GL_LIGHT1);

        // Enable lighting
        glEnable(GL_LIGHTING);

        // Enable z buffer and gouroud shading
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glShadeModel (GL_SMOOTH);
    }

    // Load skybox
    string names[6];
    names[0] = file + "box1.jpg";
    names[1] = file + "box2.jpg";
    names[2] = file + "box3.jpg";
    names[3] = file + "box4.jpg";
    names[4] = file + "box5.jpg";
    names[5] = file + "box6.jpg";
    m_skybox = new Skybox(1024, names);

    // Load spaceship
    m_ship = new SpaceCraft(file + "arrow.3ds", Vector3f(0.0, 0.0, 0.0), 3, 0.05);

    // Load Asteroidfield
    m_asteroidField = new AsteroidField(10, 
                file + "asteroid.3ds",
                2500.0f,
                3.0f,
                5.0f);

}

int MainWindow::width()
{
    return m_width;
}

int MainWindow::height()
{
    return m_height;
}

void MainWindow::execute()
{
    if(m_ship && m_ship->hasMesh() && m_sdlWindow && m_sdlGlcontext)
    {
        bool loop = true;
        const Uint8* keyStates;
       
        while (loop)
        {
            // Clear bg color and enable depth test (z-Buffer)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
                    //Handle mouse motion
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
                                    m_camera.turn(Camera::RIGHT);
                                }
                                if(event.motion.xrel < 3)
                                {
                                    m_camera.turn(Camera::LEFT);
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
                                    m_camera.move(Camera::LEFT);
                                }
                                if(event.motion.xrel < -3)
                                {
                                    m_camera.move(Camera::RIGHT);
                                } 
                                if(event.motion.yrel > 3)
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
                m_ship->handleKeyInput(keyStates);
                
            }

            // Render stuff
            m_skybox->render(m_camera);
    		m_asteroidField->render();
            m_ship->render();
            
            // Bring up back buffer 
		    SDL_GL_SwapWindow(m_sdlWindow);
        }
    }
}

MainWindow::~MainWindow()
{
    // Delete stuff
    if(m_ship)
    {
        delete m_ship;
    }

    if(m_skybox)
    {
        delete m_skybox;
    }

    if(m_asteroidField)
    {
        delete m_asteroidField;
    }

    // Cleanup SDL stuff
	SDL_GL_DeleteContext(m_sdlGlcontext);

	// Destroy our window 
	SDL_DestroyWindow(m_sdlWindow);

	// Shutdown SDL 2 
	SDL_Quit();
}

} // namespace asteroids
