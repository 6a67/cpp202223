/*
 *  Main.cpp
 *
 *  Created on: Nov. 04 2018
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "MainWindow.hpp"
#include "Camera.hpp"

#include <iostream>

int main(int argc, char** argv)
{

    if (argc != 2)
    {
        std::cout << "usage: asteroids <modelfile>" << std::endl;
        return 1;
    }

    asteroids::MainWindow window("Asteroids", argv[1], 1200, 900);

    window.execute();

    return 0;
}
