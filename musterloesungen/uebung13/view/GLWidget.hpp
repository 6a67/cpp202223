/*
 *  GLWidget.hpp
 *
 *  Created on: Jan. 14 2019
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2018 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef __GLWIDGET_HPP__
#define __GLWIDGET_HPP__

#include <string>

#include <GL/glew.h>
#include <QOpenGLWidget>

#include "view/Camera.hpp"
#include "rendering/SpaceCraft.hpp"
#include "rendering/Skybox.hpp"
#include "rendering/AsteroidField.hpp"

using namespace asteroids;
using std::shared_ptr;

/**
 * @brief   implements the OpenGL View in a QT Widget
 *
 */
class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget* parent = NULL);

    void setLevelFile(const std::string& file);
    void handleInput(map<Qt::Key, bool>& keyStates);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;

private:

    string                      m_levelFile;

    /// The virtual camera
    Camera						m_camera;

    /// A pointer to the Actor
    shared_ptr<SpaceCraft>  	m_actor;

    /// A skybox for the scene
    shared_ptr<Skybox>			m_skybox;

    /// An AsteroidField
    shared_ptr<AsteroidField>	m_asteroidField;

    QPoint                      m_mousePos;
};

#endif
