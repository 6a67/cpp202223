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
#include "io/LevelParser.hpp"
#include "io/TextureFactory.hpp"

#include <iostream>
#include <QTimer>
#include <QKeyEvent>

namespace asteroids
{

MainWindow::MainWindow(const std::string& file, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow()),
    m_timer(new QTimer())
{
    ui->setupUi(this);
    m_widget = ui->centralWidget->findChild<GLWidget*>(QString("openGLWidget"));
    m_widget->setLevelFile(file);

    connect(m_timer.get(), SIGNAL(timeout()), this, SLOT(handleInput()));
    m_timer->start(1000 / 60.0);
}

int MainWindow::width()
{
    return m_widget->width();
}

int MainWindow::height()
{
    return m_widget->height();
}

void MainWindow::handleInput()
{
    m_widget->handleInput(m_keyStates);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    m_keyStates[(Qt::Key)event->key()] = true;
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    m_keyStates[(Qt::Key)event->key()] = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

} // namespace asteroids
