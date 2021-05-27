#pragma once

#include "OpenGLNgine/Core/Exception.hpp"

#include <GL/glew.h>

#include <tuple>

namespace GL 
{

/**
 * @brief Manages the rasterizer state.
 */
class Rasterizer final
{

public:

    /**
     * @brief Sets the viewport
     * @param _width _x Left corner of the viewport.
     * @param _width _y Lower corner of the viewport.
     * @param _width Width of the viewport.
     * @param _height Height of the viewport.
     */
    static void setViewport(int _x, int _y, int _width, int _height);

    /**
     * @brief Enables or disables the scissor test.
     * @param _enable State of the scissor test.
     */
    static void enableScissorTest(bool _enable);

    /**
     * @brief Sets the scissor
     * @param _width _x Left corner of the scissor.
     * @param _width _y Lower corner of the scissor.
     * @param _width Width of the scissor.
     * @param _height Height of the scissor.
     */
    static void setScissor(int _x, int _y, int _width, int _height);

private:

    /// Automaticaly called one time.
    struct Initializer final
    {
        /// Gets the max size of the viewport.
        Initializer();
    };

    /// Defines the max size of the viewport
    static GLint s_MAX_SIZE[2];

};

}

