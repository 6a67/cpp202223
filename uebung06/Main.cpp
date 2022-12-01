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
#include "Matrix.hpp"

int main(int argc, char** argv)
{
    asteroids::MainWindow mainWindow("Asteroids", argv[1], 1024, 768);
    mainWindow.execute();

    asteroids::Vector v(1,2,3);
    v.print();

    v = v + 3;

    v.print();

    v += 0;

    v.print();




    return 0;
}
