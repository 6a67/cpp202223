/*
 *  Skybox.cpp
 *
 *  @date 18.11.2018
 *  @author Thomas Wiemann
 * 
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */
#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <string>
using std::string;

#include "Texture.hpp"
#include "ui/Camera.hpp"

namespace asteroids
{

/**
 * @brief Renders a Skybox with given dimensions
 */
class Skybox
{
public:

    /**
     * @brief Contructor. Build a skybox with the given dimensions
     *
     * @param   width   The width of the box
     * @param   files   6 filenames containing the texture image data
     */
    Skybox(int width, string files[6]);

    /**
     * @brief Dtor.
     */
    virtual ~Skybox();

    /**
     * @brief Renders the Skybox
     */
    virtual void render(Camera& cam);

private:

    /// An array containing the sykbox textures
    Texture**       m_textures;

    /// The with of the Skybox
    int             m_width;
};

} // namespace asteroids

#endif /* SKYBOX_H_ */
