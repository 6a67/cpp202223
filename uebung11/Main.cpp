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

#include "view/MainWindow.hpp"

int main(int argc, char** argv)
{
    if(argc != 5)
    {
        std::cout << "Usage: ./astroids <xml-File> <map-File> <startnode> <endnode>" << std::endl; 
    }
    else
    {
        asteroids::MainWindow mainWindow("Asteroids", argv[1], argv[2], argv[3], argv[4], 1024, 768);
        mainWindow.execute();
    }

    return 0;
}
