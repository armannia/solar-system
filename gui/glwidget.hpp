/*
 * Copyright (C) 2014
 * Computer Graphics Group, University of Siegen
 * Written by Martin Lambers <martin.lambers@uni-siegen.de>
 * All rights reserved.
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

#include <QElapsedTimer>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QTimer>


/*
 * Forward decleration
 */
class Planet;
class Sun;
class Skybox;
class CoordinateSystem;
class DeathStar;

/**
 * @brief The GLWidget class handling the opengl widget
 *
 * This class handles everything that has to do with the GL Widget.
 * It also serves as a manager for the drawable objects
 */
class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

private:

    QTimer _updateTimer;        /**< Used for regular frame updates */
    QElapsedTimer _stopWatch;   /**< Measures time between updates */

    std::shared_ptr<Planet> _earth;                 /**< The root element of the planet hierarchy */
       std::shared_ptr<Skybox> _skybox;                /**< Skybox (not part of the hierarchy */
       std::shared_ptr<CoordinateSystem> _coordSystem; /**< Coordinate system (not part of the hierarchy) */



private slots:
    /**
     * @brief animateGL updates the scene
     *
     * The new positions of all elements are generated.
     * This is not used for drawing.
     */
    void animateGL();

public:
    /**
     * @brief setGLFormat sets the GL format to 4.0 core
     */
    static void setGLFormat ()
    {
        QSurfaceFormat format;
        format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
        format.setSwapInterval(::getenv("COREGL_FPS") ? 0 : 1);
        format.setVersion(4, 0);
        format.setProfile(QSurfaceFormat::CoreProfile);
        QSurfaceFormat::setDefaultFormat(format);
    }

    /**
     * @brief GLWidget constructor
     * @param parent the parent widget
     */
    GLWidget(QWidget*& parent);

    /**
     * @brief show opens the widget
     *
     * If the widget can not start, the program exits
     */
    virtual void show();

    /**
     * @brief initializeGL initializes the context
     *
     * The function initializes GLEW and all drawable objects
     */
    virtual void initializeGL() override;

    /**
     * @brief resizeGL called automatically on resize
     * @param width the new width of the widget
     * @param height the new height of the widget
     */
    virtual void resizeGL(int width, int height) override;

    /**
     * @brief paintGL draws the scene
     */
    virtual void paintGL() override;

    /**
     * @brief mousePressEvent automatically called whenever the mouse is pressed
     * @param event the QMouseEvenent containing all relevant data
     */
    virtual void mousePressEvent(QMouseEvent * event) override;

    /**
     * @brief mouseReleaseEvent automatically called whenever the mouse is released
     * @param event the QMouseEvenent containing all relevant data
     */
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

    /**
     * @brief mousePressEvent automatically called whenever the mouse is moved
     * @param event the QMouseEvenent containing all relevant data
     */
    virtual void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * @brief mousePressEvent automatically called whenever the mouse wheel is used
     * @param event the QWheelEvent containing all relevant data
     */
    virtual void wheelEvent(QWheelEvent *event) override;

public slots:


};

#endif
