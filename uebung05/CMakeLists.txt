###############################################################################
# Declare the minimum cmake version required
###############################################################################
cmake_minimum_required(VERSION 3.0.2)

###############################################################################
# The name of out project
###############################################################################
project(CPP18_ASTEROIDS)

###############################################################################
# Now you would normally declare additional linker and include directories.
# We don't need this at this moment, just to show you how its done
###############################################################################

#link_directories("${CMAKE_SOURCE_DIR}/lib")
#link_directories("$ENV{HOME}/local/lib")

#include_directories(${CMAKE_SOURCE_DIR}/ext/Eigen)
#include_directories(${CMAKE_SOURCE_DIR})
#include_directories(${CMAKE_SOURCE_DIR}/src/lib)

###############################################################################
# Extend path to search for local cmake modules
###############################################################################

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

###############################################################################
# With cmake we can define additional compiler flags for different 
# configurations. CMAKE_CXX_FLAGS are for the default case. The debug config
# can be used to generate debug symbols for gdb. The release option uses
# special optimization flags
###############################################################################

set( CMAKE_CXX_FLAGS         "-O3 -Wall" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3 -msse3 -Wno-deprecated-declarations -Wno-unused -Wcpp" )
set( CMAKE_CXX_FLAGS_DEBUG   "-g -Wall" )

###############################################################################
# Find required libraries.Right now we need glut and OpenGL. The required 
# options forces this packages to be present. For non-mandatory packages you 
# can leave this flag out. The can then check if they were found by using
# IF(OpenGL_found) etc.
###############################################################################

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED) 

# Add SDL2 include directory to search path
include_directories(${SDL2_INCLUDE_DIR})

if(OpenGL_FOUND)
    link_directories(${OpenGL_LIBRARY_DIRS})
    include_directories(${OpenGL_INCLUDE_DIRS})
endif(OpenGL_FOUND)

if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
endif(GLEW_FOUND)

###############################################################################
# Variable for the sources of the binary. In larger projects it is often a 
# good idea to use such variables because it is easy to add more source files
# and you can reuse it for several targets (maybe you want to build a library
# some day ;-)
###############################################################################

set(ASTEROID_SOURCES
    Camera.cpp
    Main.cpp
    MainWindow.cpp  
    Model.cpp
    PLYIO.cpp
)

###############################################################################
# The executable fpr our project
###############################################################################

add_executable(asteroids ${ASTEROID_SOURCES})

###############################################################################
# External library dependencys
###############################################################################

message(STATUS ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${SDL2_LIBRARY})
target_link_libraries(asteroids ${GLEW_LIBRARIES} ${OPENGL_LIBRARY} ${SDL2_LIBRARY})

